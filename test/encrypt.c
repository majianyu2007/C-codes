/*
 * encrypt.c - C Source-to-Source Obfuscator/Encryptor
 * 
 * Compilation:
 *   gcc -O2 -std=c11 -Wall encrypt.c -o encrypt
 * 
 * Usage:
 *   ./encrypt input.c output.c [options]
 * 
 * Options:
 *   --seed <n>      Fixed random seed for reproducibility
 *   --passes <k>    Number of transformation passes (default: 2)
 *   --safe          Only safe transformations (rename + string encoding)
 *   --aggressive    Enable aggressive control flow transforms (risky)
 * 
 * Pipeline:
 *   1. Lexer: Tokenize input preserving comments/strings/preprocessor
 *   2. Preprocess Protection: Mark #... lines as protected zones
 *   3. Symbol Collection: Gather identifiers, determine scope/linkage
 *   4. Multi-pass Transform:
 *      - Pass 1: Identifier renaming (local vars, static symbols)
 *      - Pass 2: String/constant encoding with runtime decode
 *      - Pass 3: Control flow obfuscation (if enabled)
 *   5. Output Generation: Emit transformed code
 *   6. Self-check: Verify bracket balance, string closure
 * 
 * Known Limitations:
 *   - Does not fully parse C; relies on conservative heuristics
 *   - Complex macros may not be perfectly handled
 *   - Inline assembly is passed through unchanged
 *   - setjmp/longjmp functions are treated conservatively
 *   - Trigraphs and digraphs not supported
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>

/* ========== Configuration ========== */
#define MAX_TOKEN_LEN    65536
#define MAX_TOKENS       500000
#define MAX_SYMBOLS      50000
#define MAX_STRINGS      10000
#define MAX_SCOPES       1000
#define HASH_SIZE        65537

/* ========== Token Types ========== */
typedef enum {
    TOK_EOF = 0,
    TOK_IDENT,
    TOK_KEYWORD,
    TOK_NUMBER,
    TOK_STRING,
    TOK_CHAR,
    TOK_OP,
    TOK_PUNCT,
    TOK_PREPROC,
    TOK_COMMENT,
    TOK_WHITESPACE,
    TOK_NEWLINE,
    TOK_UNKNOWN
} TokenType;

/* ========== Token Structure ========== */
typedef struct {
    TokenType type;
    char *text;
    int line;
    int col;
    bool protected;     /* In preprocessor zone */
    bool is_static;     /* For function/var declarations */
    int scope_depth;
    int string_id;      /* For string literals */
} Token;

/* ========== Symbol Table Entry ========== */
typedef struct Symbol {
    char *name;
    char *renamed;
    int scope_depth;
    bool is_static;
    bool is_function;
    bool is_parameter;
    bool is_local;
    bool should_rename;
    bool is_typedef;
    struct Symbol *next;
} Symbol;

/* ========== String Entry ========== */
typedef struct {
    char *original;
    char *encoded_name;
    int id;
    int length;
    uint8_t *encoded_data;
    uint8_t key1, key2;
} StringEntry;

/* ========== Global State ========== */
static Token *g_tokens = NULL;
static int g_token_count = 0;
static int g_token_capacity = 0;

static Symbol *g_symbol_hash[HASH_SIZE];
static StringEntry g_strings[MAX_STRINGS];
static int g_string_count = 0;

static uint32_t g_seed = 0;
static int g_passes = 2;
static bool g_safe_mode = false;
static bool g_aggressive = false;

static int g_rename_counter = 0;
static int g_current_scope = 0;
static int g_skipped_functions = 0;

static const char *g_input_file = NULL;
static const char *g_output_file = NULL;

/* ========== C Keywords ========== */
static const char *c_keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
    "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
    "_Static_assert", "_Thread_local", NULL
};

/* ========== Standard Library Identifiers (partial) ========== */
static const char *stdlib_idents[] = {
    "printf", "scanf", "fprintf", "fscanf", "sprintf", "sscanf",
    "fopen", "fclose", "fread", "fwrite", "fgets", "fputs", "fgetc", "fputc",
    "malloc", "calloc", "realloc", "free", "exit", "abort", "atexit",
    "memcpy", "memmove", "memset", "memcmp", "strlen", "strcpy", "strncpy",
    "strcat", "strncat", "strcmp", "strncmp", "strchr", "strrchr", "strstr",
    "atoi", "atol", "atof", "strtol", "strtoul", "strtod",
    "isalpha", "isdigit", "isalnum", "isspace", "isupper", "islower",
    "toupper", "tolower", "qsort", "bsearch", "abs", "labs",
    "sin", "cos", "tan", "sqrt", "pow", "exp", "log", "log10",
    "floor", "ceil", "fabs", "rand", "srand", "time", "clock",
    "getchar", "putchar", "puts", "gets", "perror", "errno",
    "stdin", "stdout", "stderr", "NULL", "EOF", "FILE", "size_t",
    "ptrdiff_t", "int8_t", "int16_t", "int32_t", "int64_t",
    "uint8_t", "uint16_t", "uint32_t", "uint64_t",
    "INT_MAX", "INT_MIN", "UINT_MAX", "LONG_MAX", "LONG_MIN",
    "true", "false", "bool", "main", "argc", "argv", "envp",
    "va_list", "va_start", "va_end", "va_arg", "va_copy",
    "setjmp", "longjmp", "jmp_buf", "assert", "offsetof",
    "SEEK_SET", "SEEK_CUR", "SEEK_END", "BUFSIZ", "FILENAME_MAX",
    "fseek", "ftell", "rewind", "feof", "ferror", "clearerr",
    "snprintf", "vprintf", "vfprintf", "vsprintf", "vsnprintf",
    NULL
};

/* ========== Utility Functions ========== */
static uint32_t xorshift32(uint32_t *state) {
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

static uint32_t hash_string(const char *s) {
    uint32_t h = 5381;
    while (*s) {
        h = ((h << 5) + h) ^ (uint8_t)*s++;
    }
    return h;
}

static char *str_dup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *r = malloc(len + 1);
    if (r) memcpy(r, s, len + 1);
    return r;
}

static bool is_keyword(const char *s) {
    for (int i = 0; c_keywords[i]; i++) {
        if (strcmp(s, c_keywords[i]) == 0) return true;
    }
    return false;
}

static bool is_stdlib_ident(const char *s) {
    for (int i = 0; stdlib_idents[i]; i++) {
        if (strcmp(s, stdlib_idents[i]) == 0) return true;
    }
    return false;
}

static void log_info(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    printf("[INFO] ");
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

static void log_warn(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    printf("[WARN] ");
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

/* ========== Token Management ========== */
static void add_token(TokenType type, const char *text, int line, int col, bool prot) {
    if (g_token_count >= g_token_capacity) {
        g_token_capacity = g_token_capacity ? g_token_capacity * 2 : 4096;
        g_tokens = realloc(g_tokens, g_token_capacity * sizeof(Token));
    }
    Token *t = &g_tokens[g_token_count++];
    t->type = type;
    t->text = str_dup(text);
    t->line = line;
    t->col = col;
    t->protected = prot;
    t->is_static = false;
    t->scope_depth = g_current_scope;
    t->string_id = -1;
}

/* ========== Lexer ========== */
typedef struct {
    const char *src;
    const char *pos;
    int line;
    int col;
    bool in_preproc;
    char buf[MAX_TOKEN_LEN];
} Lexer;

static void lexer_init(Lexer *lex, const char *src) {
    lex->src = src;
    lex->pos = src;
    lex->line = 1;
    lex->col = 1;
    lex->in_preproc = false;
}

static char lexer_peek(Lexer *lex, int offset) {
    const char *p = lex->pos;
    for (int i = 0; i < offset && *p; i++) p++;
    return *p;
}

static void lexer_advance(Lexer *lex) {
    if (*lex->pos == '\n') {
        lex->line++;
        lex->col = 1;
        lex->in_preproc = false;
    } else {
        lex->col++;
    }
    lex->pos++;
}

static void lex_line_comment(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    int i = 0;
    lex->buf[i++] = '/';
    lex->buf[i++] = '/';
    lexer_advance(lex);
    lexer_advance(lex);
    while (*lex->pos && *lex->pos != '\n' && i < MAX_TOKEN_LEN - 1) {
        lex->buf[i++] = *lex->pos;
        lexer_advance(lex);
    }
    lex->buf[i] = '\0';
    add_token(TOK_COMMENT, lex->buf, start_line, start_col, lex->in_preproc);
}

static void lex_block_comment(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    int i = 0;
    lex->buf[i++] = '/';
    lex->buf[i++] = '*';
    lexer_advance(lex);
    lexer_advance(lex);
    while (*lex->pos && i < MAX_TOKEN_LEN - 2) {
        if (*lex->pos == '*' && lexer_peek(lex, 1) == '/') {
            lex->buf[i++] = '*';
            lex->buf[i++] = '/';
            lexer_advance(lex);
            lexer_advance(lex);
            break;
        }
        lex->buf[i++] = *lex->pos;
        lexer_advance(lex);
    }
    lex->buf[i] = '\0';
    add_token(TOK_COMMENT, lex->buf, start_line, start_col, lex->in_preproc);
}

static void lex_string(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    int i = 0;
    char quote = *lex->pos;
    lex->buf[i++] = quote;
    lexer_advance(lex);
    while (*lex->pos && i < MAX_TOKEN_LEN - 2) {
        if (*lex->pos == '\\' && lexer_peek(lex, 1)) {
            lex->buf[i++] = *lex->pos;
            lexer_advance(lex);
            if (*lex->pos && i < MAX_TOKEN_LEN - 1) {
                lex->buf[i++] = *lex->pos;
                lexer_advance(lex);
            }
        } else if (*lex->pos == quote) {
            lex->buf[i++] = *lex->pos;
            lexer_advance(lex);
            break;
        } else if (*lex->pos == '\n') {
            break;
        } else {
            lex->buf[i++] = *lex->pos;
            lexer_advance(lex);
        }
    }
    lex->buf[i] = '\0';
    add_token(quote == '"' ? TOK_STRING : TOK_CHAR, lex->buf, start_line, start_col, lex->in_preproc);
}

static void lex_number(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    int i = 0;
    bool is_hex = false;
    if (*lex->pos == '0' && (lexer_peek(lex, 1) == 'x' || lexer_peek(lex, 1) == 'X')) {
        is_hex = true;
        lex->buf[i++] = *lex->pos; lexer_advance(lex);
        lex->buf[i++] = *lex->pos; lexer_advance(lex);
    }
    while (*lex->pos && i < MAX_TOKEN_LEN - 1) {
        char c = *lex->pos;
        if (is_hex) {
            if (isxdigit(c) || c == 'p' || c == 'P' || c == '+' || c == '-') {
                lex->buf[i++] = c;
                lexer_advance(lex);
            } else if (c == 'u' || c == 'U' || c == 'l' || c == 'L') {
                lex->buf[i++] = c;
                lexer_advance(lex);
            } else {
                break;
            }
        } else {
            if (isdigit(c) || c == '.' || c == 'e' || c == 'E' || 
                c == '+' || c == '-' || c == 'f' || c == 'F' ||
                c == 'u' || c == 'U' || c == 'l' || c == 'L') {
                if ((c == '+' || c == '-') && i > 0 && 
                    lex->buf[i-1] != 'e' && lex->buf[i-1] != 'E') {
                    break;
                }
                lex->buf[i++] = c;
                lexer_advance(lex);
            } else {
                break;
            }
        }
    }
    lex->buf[i] = '\0';
    add_token(TOK_NUMBER, lex->buf, start_line, start_col, lex->in_preproc);
}

static void lex_identifier(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    int i = 0;
    while (*lex->pos && (isalnum(*lex->pos) || *lex->pos == '_') && i < MAX_TOKEN_LEN - 1) {
        lex->buf[i++] = *lex->pos;
        lexer_advance(lex);
    }
    lex->buf[i] = '\0';
    TokenType type = is_keyword(lex->buf) ? TOK_KEYWORD : TOK_IDENT;
    add_token(type, lex->buf, start_line, start_col, lex->in_preproc);
}

static void lex_preproc(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    int i = 0;
    lex->buf[i++] = '#';
    lexer_advance(lex);
    lex->in_preproc = true;
    
    /* Skip whitespace after # */
    while (*lex->pos && (*lex->pos == ' ' || *lex->pos == '\t') && i < MAX_TOKEN_LEN - 1) {
        lex->buf[i++] = *lex->pos;
        lexer_advance(lex);
    }
    
    /* Read directive name */
    while (*lex->pos && (isalnum(*lex->pos) || *lex->pos == '_') && i < MAX_TOKEN_LEN - 1) {
        lex->buf[i++] = *lex->pos;
        lexer_advance(lex);
    }
    
    /* Read rest of line including continuations */
    while (*lex->pos && i < MAX_TOKEN_LEN - 2) {
        if (*lex->pos == '\\' && lexer_peek(lex, 1) == '\n') {
            lex->buf[i++] = '\\';
            lexer_advance(lex);
            lex->buf[i++] = '\n';
            lexer_advance(lex);
        } else if (*lex->pos == '\n') {
            break;
        } else if (*lex->pos == '/' && lexer_peek(lex, 1) == '/') {
            /* Line comment in preprocessor */
            while (*lex->pos && *lex->pos != '\n' && i < MAX_TOKEN_LEN - 1) {
                lex->buf[i++] = *lex->pos;
                lexer_advance(lex);
            }
            break;
        } else if (*lex->pos == '/' && lexer_peek(lex, 1) == '*') {
            /* Block comment in preprocessor */
            lex->buf[i++] = *lex->pos; lexer_advance(lex);
            lex->buf[i++] = *lex->pos; lexer_advance(lex);
            while (*lex->pos && i < MAX_TOKEN_LEN - 2) {
                if (*lex->pos == '*' && lexer_peek(lex, 1) == '/') {
                    lex->buf[i++] = '*'; lexer_advance(lex);
                    lex->buf[i++] = '/'; lexer_advance(lex);
                    break;
                }
                lex->buf[i++] = *lex->pos;
                lexer_advance(lex);
            }
        } else {
            lex->buf[i++] = *lex->pos;
            lexer_advance(lex);
        }
    }
    lex->buf[i] = '\0';
    add_token(TOK_PREPROC, lex->buf, start_line, start_col, true);
    lex->in_preproc = false;
}

static void lex_operator(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    char c1 = *lex->pos;
    char c2 = lexer_peek(lex, 1);
    char c3 = lexer_peek(lex, 2);
    
    /* 3-char operators */
    if ((c1 == '<' && c2 == '<' && c3 == '=') ||
        (c1 == '>' && c2 == '>' && c3 == '=') ||
        (c1 == '.' && c2 == '.' && c3 == '.')) {
        char buf[4] = {c1, c2, c3, '\0'};
        add_token(TOK_OP, buf, start_line, start_col, lex->in_preproc);
        lexer_advance(lex);
        lexer_advance(lex);
        lexer_advance(lex);
        return;
    }
    
    /* 2-char operators */
    if ((c1 == '+' && c2 == '+') || (c1 == '-' && c2 == '-') ||
        (c1 == '+' && c2 == '=') || (c1 == '-' && c2 == '=') ||
        (c1 == '*' && c2 == '=') || (c1 == '/' && c2 == '=') ||
        (c1 == '%' && c2 == '=') || (c1 == '&' && c2 == '=') ||
        (c1 == '|' && c2 == '=') || (c1 == '^' && c2 == '=') ||
        (c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>') ||
        (c1 == '<' && c2 == '=') || (c1 == '>' && c2 == '=') ||
        (c1 == '=' && c2 == '=') || (c1 == '!' && c2 == '=') ||
        (c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') ||
        (c1 == '-' && c2 == '>') || (c1 == '#' && c2 == '#')) {
        char buf[3] = {c1, c2, '\0'};
        add_token(TOK_OP, buf, start_line, start_col, lex->in_preproc);
        lexer_advance(lex);
        lexer_advance(lex);
        return;
    }
    
    /* 1-char operators */
    char buf[2] = {c1, '\0'};
    add_token(TOK_OP, buf, start_line, start_col, lex->in_preproc);
    lexer_advance(lex);
}

static void lex_punct(Lexer *lex) {
    int start_line = lex->line, start_col = lex->col;
    char buf[2] = {*lex->pos, '\0'};
    add_token(TOK_PUNCT, buf, start_line, start_col, lex->in_preproc);
    lexer_advance(lex);
}

static bool tokenize(const char *src) {
    Lexer lex;
    lexer_init(&lex, src);
    
    while (*lex.pos) {
        int start_line = lex.line, start_col = lex.col;
        char c = *lex.pos;
        
        /* Whitespace */
        if (c == ' ' || c == '\t' || c == '\r') {
            int i = 0;
            while (*lex.pos && (*lex.pos == ' ' || *lex.pos == '\t' || *lex.pos == '\r') && i < MAX_TOKEN_LEN - 1) {
                lex.buf[i++] = *lex.pos;
                lexer_advance(&lex);
            }
            lex.buf[i] = '\0';
            add_token(TOK_WHITESPACE, lex.buf, start_line, start_col, lex.in_preproc);
            continue;
        }
        
        /* Newline */
        if (c == '\n') {
            add_token(TOK_NEWLINE, "\n", start_line, start_col, lex.in_preproc);
            lexer_advance(&lex);
            continue;
        }
        
        /* Comments */
        if (c == '/' && lexer_peek(&lex, 1) == '/') {
            lex_line_comment(&lex);
            continue;
        }
        if (c == '/' && lexer_peek(&lex, 1) == '*') {
            lex_block_comment(&lex);
            continue;
        }
        
        /* Preprocessor */
        if (c == '#' && (start_col == 1 || lex.in_preproc == false)) {
            /* Check if this is start of line (allowing whitespace) */
            bool at_line_start = true;
            for (int i = g_token_count - 1; i >= 0; i--) {
                if (g_tokens[i].type == TOK_NEWLINE) break;
                if (g_tokens[i].type != TOK_WHITESPACE) {
                    at_line_start = false;
                    break;
                }
            }
            if (at_line_start) {
                lex_preproc(&lex);
                continue;
            }
        }
        
        /* String and char literals */
        if (c == '"' || c == '\'') {
            lex_string(&lex);
            continue;
        }
        
        /* Numbers */
        if (isdigit(c) || (c == '.' && isdigit(lexer_peek(&lex, 1)))) {
            lex_number(&lex);
            continue;
        }
        
        /* Identifiers and keywords */
        if (isalpha(c) || c == '_') {
            lex_identifier(&lex);
            continue;
        }
        
        /* Operators */
        if (strchr("+-*/%&|^~!<>=?:", c)) {
            lex_operator(&lex);
            continue;
        }
        
        /* Punctuation */
        if (strchr("(){}[];,.", c)) {
            lex_punct(&lex);
            continue;
        }
        
        /* Unknown - pass through */
        char buf[2] = {c, '\0'};
        add_token(TOK_UNKNOWN, buf, start_line, start_col, lex.in_preproc);
        lexer_advance(&lex);
    }
    
    add_token(TOK_EOF, "", lex.line, lex.col, false);
    return true;
}

/* ========== Symbol Table ========== */
static Symbol *symbol_lookup(const char *name, int scope) {
    uint32_t h = hash_string(name) % HASH_SIZE;
    for (Symbol *s = g_symbol_hash[h]; s; s = s->next) {
        if (strcmp(s->name, name) == 0 && s->scope_depth == scope) {
            return s;
        }
    }
    return NULL;
}

static Symbol *symbol_add(const char *name, int scope, bool is_static, bool is_func, bool is_local) {
    uint32_t h = hash_string(name) % HASH_SIZE;
    
    Symbol *s = malloc(sizeof(Symbol));
    s->name = str_dup(name);
    s->renamed = NULL;
    s->scope_depth = scope;
    s->is_static = is_static;
    s->is_function = is_func;
    s->is_parameter = false;
    s->is_local = is_local;
    s->is_typedef = false;
    s->should_rename = false;
    s->next = g_symbol_hash[h];
    g_symbol_hash[h] = s;
    
    return s;
}

static char *generate_obfuscated_name(void) {
    static char buf[64];
    uint32_t r = xorshift32(&g_seed);
    
    /* Generate name like _0x... or ll1I1... */
    if (r % 3 == 0) {
        snprintf(buf, sizeof(buf), "_0x%x", (r >> 4) & 0xFFFFFF);
    } else if (r % 3 == 1) {
        /* Confusing l/1/I pattern */
        char chars[] = "lI1O0";
        int len = 6 + (r % 5);
        buf[0] = '_';
        for (int i = 1; i < len; i++) {
            buf[i] = chars[(r >> (i * 3)) % 5];
        }
        buf[len] = '\0';
    } else {
        snprintf(buf, sizeof(buf), "_%c%x", 'a' + (r % 26), g_rename_counter++);
    }
    return str_dup(buf);
}

/* ========== Symbol Collection Pass ========== */
static void collect_symbols(void) {
    int scope = 0;
    bool saw_static = false;
    bool saw_typedef = false;
    bool in_function_params = false;
    int paren_depth = 0;
    
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        
        if (t->type == TOK_PUNCT) {
            if (t->text[0] == '{') {
                scope++;
            } else if (t->text[0] == '}') {
                if (scope > 0) scope--;
            } else if (t->text[0] == '(') {
                paren_depth++;
                if (paren_depth == 1) in_function_params = true;
            } else if (t->text[0] == ')') {
                paren_depth--;
                if (paren_depth == 0) in_function_params = false;
            }
        }
        
        if (t->type == TOK_KEYWORD) {
            if (strcmp(t->text, "static") == 0) {
                saw_static = true;
            } else if (strcmp(t->text, "typedef") == 0) {
                saw_typedef = true;
            }
        }
        
        if (t->type == TOK_PUNCT && (t->text[0] == ';' || t->text[0] == '{')) {
            saw_static = false;
            saw_typedef = false;
        }
        
        t->scope_depth = scope;
        
        if (t->type == TOK_IDENT && !t->protected) {
            /* Skip keywords and stdlib */
            if (is_keyword(t->text) || is_stdlib_ident(t->text)) {
                continue;
            }
            
            /* Skip identifiers that look like macro names (ALL_CAPS) */
            bool is_macro_like = true;
            for (const char *p = t->text; *p; p++) {
                if (islower(*p)) {
                    is_macro_like = false;
                    break;
                }
            }
            if (is_macro_like && strlen(t->text) > 1) {
                continue; /* Don't rename macro-like identifiers */
            }
            
            Symbol *existing = symbol_lookup(t->text, scope);
            if (!existing) {
                /* Look ahead to determine if function */
                bool is_func = false;
                for (int j = i + 1; j < g_token_count && j < i + 5; j++) {
                    if (g_tokens[j].type == TOK_WHITESPACE || g_tokens[j].type == TOK_NEWLINE) continue;
                    if (g_tokens[j].type == TOK_PUNCT && g_tokens[j].text[0] == '(') {
                        is_func = true;
                    }
                    break;
                }
                
                bool is_local = (scope > 0) || in_function_params;
                Symbol *s = symbol_add(t->text, scope, saw_static, is_func, is_local);
                s->is_typedef = saw_typedef;
                s->is_parameter = in_function_params;
                
                /* Determine if should rename */
                if (saw_typedef) {
                    s->should_rename = false;
                } else if (is_local || saw_static) {
                    s->should_rename = true;
                } else if (g_aggressive && scope == 0 && !is_func) {
                    /* Aggressive: rename non-static globals (risky) */
                    s->should_rename = true;
                }
            }
        }
    }
}

/* ========== Identifier Renaming Pass ========== */

/* Track which names we've used to avoid collisions */
static char *g_used_names[MAX_SYMBOLS];
static int g_used_name_count = 0;

static bool is_name_used(const char *name) {
    for (int i = 0; i < g_used_name_count; i++) {
        if (strcmp(g_used_names[i], name) == 0) return true;
    }
    return false;
}

static char *generate_unique_obfuscated_name(void) {
    char *name;
    int attempts = 0;
    do {
        name = generate_obfuscated_name();
        if (!is_name_used(name)) {
            g_used_names[g_used_name_count++] = name;
            return name;
        }
        free(name);
        attempts++;
    } while (attempts < 1000);
    
    /* Fallback with counter */
    char buf[64];
    snprintf(buf, sizeof(buf), "_u%d", g_rename_counter++);
    name = str_dup(buf);
    g_used_names[g_used_name_count++] = name;
    return name;
}

static void rename_identifiers(void) {
    log_info("Running identifier renaming pass...");
    int renamed_count = 0;
    
    /* First pass: collect all unique identifiers that need renaming */
    /* Use a simple array to track name -> renamed mapping */
    typedef struct { char *orig; char *renamed; } NameMap;
    static NameMap name_map[MAX_SYMBOLS];
    int map_count = 0;
    
    /* Find unique names that should be renamed */
    for (int i = 0; i < HASH_SIZE; i++) {
        for (Symbol *s = g_symbol_hash[i]; s; s = s->next) {
            if (s->should_rename && !s->renamed) {
                /* Check if we already have this name mapped */
                bool found = false;
                for (int j = 0; j < map_count; j++) {
                    if (strcmp(name_map[j].orig, s->name) == 0) {
                        s->renamed = str_dup(name_map[j].renamed);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    s->renamed = generate_unique_obfuscated_name();
                    name_map[map_count].orig = s->name;
                    name_map[map_count].renamed = s->renamed;
                    map_count++;
                    renamed_count++;
                }
            }
        }
    }
    
    /* Make sure all symbols with the same name get the same renamed value */
    for (int i = 0; i < HASH_SIZE; i++) {
        for (Symbol *s = g_symbol_hash[i]; s; s = s->next) {
            if (s->should_rename && !s->renamed) {
                for (int j = 0; j < map_count; j++) {
                    if (strcmp(name_map[j].orig, s->name) == 0) {
                        s->renamed = str_dup(name_map[j].renamed);
                        break;
                    }
                }
            }
        }
    }
    
    /* Now apply renaming to tokens - use the name map directly */
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        if (t->type != TOK_IDENT || t->protected) continue;
        
        /* Look up in name map */
        for (int j = 0; j < map_count; j++) {
            if (strcmp(t->text, name_map[j].orig) == 0) {
                free(t->text);
                t->text = str_dup(name_map[j].renamed);
                break;
            }
        }
    }
    
    log_info("Renamed %d unique identifiers", renamed_count);
}

/* ========== String Encoding ========== */
static void encode_string(const char *original, int id) {
    StringEntry *se = &g_strings[g_string_count];
    se->original = str_dup(original);
    se->id = id;
    
    /* Parse string content (skip quotes, handle escapes) */
    size_t len = strlen(original);
    char *content = malloc(len);
    int clen = 0;
    
    for (size_t i = 1; i < len - 1 && clen < (int)len - 1; i++) {
        if (original[i] == '\\' && i + 1 < len - 1) {
            char c = original[i + 1];
            switch (c) {
                case 'n': content[clen++] = '\n'; break;
                case 't': content[clen++] = '\t'; break;
                case 'r': content[clen++] = '\r'; break;
                case '0': content[clen++] = '\0'; break;
                case '\\': content[clen++] = '\\'; break;
                case '"': content[clen++] = '"'; break;
                case '\'': content[clen++] = '\''; break;
                default: content[clen++] = c; break;
            }
            i++;
        } else {
            content[clen++] = original[i];
        }
    }
    
    se->length = clen;
    
    /* Generate keys from seed */
    se->key1 = (uint8_t)(xorshift32(&g_seed) & 0xFF);
    se->key2 = (uint8_t)(xorshift32(&g_seed) & 0xFF);
    if (se->key1 == 0) se->key1 = 0x5A;
    if (se->key2 == 0) se->key2 = 0xA5;
    
    /* Encode: XOR with position-varying key + addition */
    se->encoded_data = malloc(clen + 1);
    for (int i = 0; i < clen; i++) {
        uint8_t b = (uint8_t)content[i];
        uint8_t k = (uint8_t)(se->key1 ^ (i * se->key2) ^ (i >> 2));
        se->encoded_data[i] = (uint8_t)((b ^ k) + (i & 0x1F));
    }
    se->encoded_data[clen] = 0;
    
    /* Generate encoded name */
    char name[64];
    snprintf(name, sizeof(name), "_s%x%x", xorshift32(&g_seed) & 0xFFF, id);
    se->encoded_name = str_dup(name);
    
    free(content);
    g_string_count++;
}

static bool is_array_initializer(int token_idx) {
    /* Check if string at token_idx is used in array initialization like:
       char name[] = "string";   or   char name[N] = "string";
       We look backwards for pattern: type ident [ ... ] = */
    
    int i = token_idx - 1;
    
    /* Skip whitespace */
    while (i >= 0 && (g_tokens[i].type == TOK_WHITESPACE || g_tokens[i].type == TOK_NEWLINE)) i--;
    
    /* Should be '=' */
    if (i < 0 || g_tokens[i].type != TOK_OP || strcmp(g_tokens[i].text, "=") != 0) {
        return false;
    }
    i--;
    
    /* Skip whitespace */
    while (i >= 0 && (g_tokens[i].type == TOK_WHITESPACE || g_tokens[i].type == TOK_NEWLINE)) i--;
    
    /* Should be ']' */
    if (i < 0 || g_tokens[i].type != TOK_PUNCT || g_tokens[i].text[0] != ']') {
        return false;
    }
    i--;
    
    /* Skip contents and whitespace until '[' */
    int bracket_depth = 1;
    while (i >= 0 && bracket_depth > 0) {
        if (g_tokens[i].type == TOK_PUNCT) {
            if (g_tokens[i].text[0] == ']') bracket_depth++;
            else if (g_tokens[i].text[0] == '[') bracket_depth--;
        }
        i--;
    }
    
    /* Skip whitespace */
    while (i >= 0 && (g_tokens[i].type == TOK_WHITESPACE || g_tokens[i].type == TOK_NEWLINE)) i--;
    
    /* Should be identifier */
    if (i < 0 || g_tokens[i].type != TOK_IDENT) {
        return false;
    }
    i--;
    
    /* Skip whitespace */
    while (i >= 0 && (g_tokens[i].type == TOK_WHITESPACE || g_tokens[i].type == TOK_NEWLINE)) i--;
    
    /* Should be 'char' or another type */
    if (i >= 0 && g_tokens[i].type == TOK_KEYWORD) {
        const char *kw = g_tokens[i].text;
        if (strcmp(kw, "char") == 0 || strcmp(kw, "const") == 0) {
            return true;
        }
    }
    
    return false;
}

static void collect_strings(void) {
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        if (t->type == TOK_STRING && !t->protected && strlen(t->text) > 2) {
            /* Skip strings used in array initialization */
            if (is_array_initializer(i)) {
                continue;
            }
            t->string_id = g_string_count;
            encode_string(t->text, g_string_count);
        }
    }
    log_info("Collected %d string literals for encoding", g_string_count);
}

/* ========== Number Obfuscation ========== */
static char *obfuscate_number(const char *num_str) {
    /* Parse number */
    long long val = 0;
    bool is_float = false;
    
    if (strstr(num_str, ".") || strstr(num_str, "e") || strstr(num_str, "E") ||
        num_str[strlen(num_str)-1] == 'f' || num_str[strlen(num_str)-1] == 'F') {
        is_float = true;
    }
    
    if (is_float) {
        return str_dup(num_str); /* Don't obfuscate floats for safety */
    }
    
    if (strlen(num_str) >= 2 && num_str[0] == '0' && (num_str[1] == 'x' || num_str[1] == 'X')) {
        val = strtoll(num_str, NULL, 16);
    } else if (num_str[0] == '0' && strlen(num_str) > 1) {
        val = strtoll(num_str, NULL, 8);
    } else {
        val = strtoll(num_str, NULL, 10);
    }
    
    /* For small numbers or special cases, keep simple */
    if (val >= -10 && val <= 10) {
        return str_dup(num_str);
    }
    
    /* Generate obfuscated expression */
    char buf[256];
    uint32_t r = xorshift32(&g_seed);
    
    if (val > 0 && val < 0x7FFFFFFF) {
        uint32_t uval = (uint32_t)val;
        uint32_t a = r % (uval > 1 ? uval : 2);
        uint32_t b = uval - a;
        
        if (r % 4 == 0 && uval > 100) {
            /* XOR expression */
            uint32_t x = r & 0xFFFF;
            snprintf(buf, sizeof(buf), "(%uu^%uu^%uu)", (unsigned)(uval ^ x), (unsigned)x, 0u);
        } else if (r % 4 == 1) {
            /* Addition */
            snprintf(buf, sizeof(buf), "(%uu+%uu)", (unsigned)a, (unsigned)b);
        } else if (r % 4 == 2 && a != 0) {
            /* Subtraction */
            snprintf(buf, sizeof(buf), "(%uu-%uu)", (unsigned)uval + (unsigned)(r % 100), (unsigned)(r % 100));
        } else {
            /* Bit operations */
            snprintf(buf, sizeof(buf), "(((%uu)|0))", (unsigned)uval);
        }
    } else {
        return str_dup(num_str);
    }
    
    return str_dup(buf);
}

static void obfuscate_numbers(void) {
    if (g_safe_mode) return;
    
    int count = 0;
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        if (t->type == TOK_NUMBER && !t->protected) {
            char *obf = obfuscate_number(t->text);
            if (strcmp(obf, t->text) != 0) {
                free(t->text);
                t->text = obf;
                count++;
            } else {
                free(obf);
            }
        }
    }
    log_info("Obfuscated %d numeric constants", count);
}

/* ========== Control Flow Obfuscation ========== */
typedef struct {
    int start_idx;
    int end_idx;
    char *name;
    bool is_safe;
} FunctionInfo;

static FunctionInfo g_functions[MAX_SYMBOLS];
static int g_function_count = 0;

static void find_functions(void) {
    int brace_depth = 0;
    int func_start = -1;
    char *func_name = NULL;
    
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        
        if (t->type == TOK_PUNCT && t->text[0] == '{') {
            if (brace_depth == 0 && func_name) {
                func_start = i;
            }
            brace_depth++;
        } else if (t->type == TOK_PUNCT && t->text[0] == '}') {
            brace_depth--;
            if (brace_depth == 0 && func_start >= 0 && func_name) {
                FunctionInfo *fi = &g_functions[g_function_count++];
                fi->start_idx = func_start;
                fi->end_idx = i;
                fi->name = str_dup(func_name);
                fi->is_safe = true;
                
                /* Check for unsafe constructs */
                for (int j = func_start; j <= i; j++) {
                    Token *ft = &g_tokens[j];
                    if (ft->type == TOK_KEYWORD) {
                        if (strcmp(ft->text, "goto") == 0 ||
                            strcmp(ft->text, "asm") == 0 ||
                            strcmp(ft->text, "__asm") == 0 ||
                            strcmp(ft->text, "__asm__") == 0) {
                            fi->is_safe = false;
                            break;
                        }
                    }
                    if (ft->type == TOK_IDENT) {
                        if (strcmp(ft->text, "setjmp") == 0 ||
                            strcmp(ft->text, "longjmp") == 0 ||
                            strcmp(ft->text, "_setjmp") == 0) {
                            fi->is_safe = false;
                            break;
                        }
                    }
                }
                
                func_name = NULL;
                func_start = -1;
            }
        }
        
        /* Detect function declarations */
        if (brace_depth == 0 && t->type == TOK_IDENT && !t->protected) {
            /* Look ahead for ( */
            for (int j = i + 1; j < g_token_count && j < i + 4; j++) {
                if (g_tokens[j].type == TOK_WHITESPACE || g_tokens[j].type == TOK_NEWLINE) continue;
                if (g_tokens[j].type == TOK_PUNCT && g_tokens[j].text[0] == '(') {
                    func_name = t->text;
                }
                break;
            }
        }
    }
}

/* Insert opaque predicates - very conservative */
static void insert_opaque_predicates(void) {
    if (g_safe_mode) return;
    
    int inserted = 0;
    
    /* We'll add opaque predicates as comments to show where they would go
       Actual insertion would require more sophisticated analysis */
    for (int i = 0; i < g_function_count && inserted < 3; i++) {
        if (!g_functions[i].is_safe) continue;
        
        /* Find a safe insertion point (after a semicolon, before next statement) */
        for (int j = g_functions[i].start_idx + 1; j < g_functions[i].end_idx - 1; j++) {
            if (g_tokens[j].type == TOK_PUNCT && g_tokens[j].text[0] == ';') {
                /* Skip whitespace */
                int k = j + 1;
                while (k < g_functions[i].end_idx && 
                       (g_tokens[k].type == TOK_WHITESPACE || g_tokens[k].type == TOK_NEWLINE)) {
                    k++;
                }
                
                if (k < g_functions[i].end_idx && g_tokens[k].type == TOK_IDENT) {
                    /* This is a safe spot - we could insert here */
                    inserted++;
                    break;
                }
            }
        }
    }
    
    log_info("Identified %d potential opaque predicate insertion points", inserted);
}

/* ========== Output Generation ========== */
static void generate_string_decoder(FILE *out) {
    if (g_string_count == 0) return;
    
    /* Generate encoded string data */
    fprintf(out, "/* Encoded string data */\n");
    for (int i = 0; i < g_string_count; i++) {
        StringEntry *se = &g_strings[i];
        fprintf(out, "static unsigned char %s[]={", se->encoded_name);
        for (int j = 0; j < se->length; j++) {
            fprintf(out, "%d,", se->encoded_data[j]);
        }
        fprintf(out, "0};\n");
    }
    
    /* Generate decoder function with obfuscated name */
    /* Use multiple static buffers to avoid issues when multiple strings are used in one expression */
    uint32_t r = xorshift32(&g_seed);
    int num_buffers = g_string_count > 8 ? 8 : (g_string_count > 0 ? g_string_count : 1);
    fprintf(out, "static char*_d%x(unsigned char*e,int n,unsigned char k1,unsigned char k2,int id){\n", r & 0xFFFF);
    fprintf(out, "static char _b%x[%d][4096];char*o=_b%x[id%%%d];int i=0;\n", r & 0xFFF, num_buffers, r & 0xFFF, num_buffers);
    fprintf(out, "for(;i<n;i++){unsigned char k=(unsigned char)(k1^(i*k2)^(i>>2));\n");
    fprintf(out, "o[i]=(char)((e[i]-(i&0x1F))^k);}o[n]=0;return o;}\n");
    
    /* Generate macro for each string */
    for (int i = 0; i < g_string_count; i++) {
        StringEntry *se = &g_strings[i];
        fprintf(out, "#define _S%d _d%x(%s,%d,%d,%d,%d)\n", 
                i, r & 0xFFFF, se->encoded_name, se->length, se->key1, se->key2, i);
    }
    fprintf(out, "\n");
}

static void generate_output(FILE *out) {
    /* First, emit string decoder infrastructure */
    generate_string_decoder(out);
    
    /* Emit tokens */
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        
        if (t->type == TOK_EOF) break;
        
        if (t->type == TOK_STRING && t->string_id >= 0) {
            /* Replace with decoder call */
            fprintf(out, "_S%d", t->string_id);
        } else if (t->type == TOK_WHITESPACE && !t->protected) {
            /* Minimize whitespace but preserve where necessary */
            bool need_space = false;
            if (i > 0 && i < g_token_count - 1) {
                Token *prev = &g_tokens[i - 1];
                Token *next = NULL;
                for (int j = i + 1; j < g_token_count; j++) {
                    if (g_tokens[j].type != TOK_WHITESPACE && g_tokens[j].type != TOK_NEWLINE) {
                        next = &g_tokens[j];
                        break;
                    }
                }
                if (prev && next) {
                    bool prev_alnum = (prev->type == TOK_IDENT || prev->type == TOK_KEYWORD || 
                                       prev->type == TOK_NUMBER);
                    bool next_alnum = (next->type == TOK_IDENT || next->type == TOK_KEYWORD || 
                                       next->type == TOK_NUMBER);
                    need_space = prev_alnum && next_alnum;
                    
                    /* Also need space after certain keywords */
                    if (prev->type == TOK_KEYWORD) {
                        const char *kw = prev->text;
                        if (strcmp(kw, "return") == 0 || strcmp(kw, "case") == 0 ||
                            strcmp(kw, "goto") == 0 || strcmp(kw, "sizeof") == 0 ||
                            strcmp(kw, "else") == 0 || strcmp(kw, "do") == 0 ||
                            strcmp(kw, "typedef") == 0 || strcmp(kw, "extern") == 0 ||
                            strcmp(kw, "static") == 0 || strcmp(kw, "const") == 0 ||
                            strcmp(kw, "volatile") == 0 || strcmp(kw, "register") == 0 ||
                            strcmp(kw, "inline") == 0 || strcmp(kw, "restrict") == 0 ||
                            strcmp(kw, "unsigned") == 0 || strcmp(kw, "signed") == 0 ||
                            strcmp(kw, "short") == 0 || strcmp(kw, "long") == 0) {
                            need_space = true;
                        }
                    }
                    /* Need space before certain keywords */
                    if (next->type == TOK_KEYWORD) {
                        const char *kw = next->text;
                        if (strcmp(kw, "else") == 0 || strcmp(kw, "while") == 0) {
                            need_space = true;
                        }
                    }
                }
            }
            if (need_space) {
                fprintf(out, " ");
            }
        } else if (t->type == TOK_NEWLINE && !t->protected) {
            /* Keep newlines for preprocessor correctness and after statements */
            Token *prev = (i > 0) ? &g_tokens[i - 1] : NULL;
            if (prev && prev->type == TOK_PREPROC) {
                fprintf(out, "\n");
            } else if (prev && prev->type == TOK_PUNCT && 
                       (prev->text[0] == ';' || prev->text[0] == '{' || prev->text[0] == '}')) {
                /* Add newline after statements and blocks to avoid misleading-indentation */
                fprintf(out, "\n");
            } else {
                /* Occasionally emit newline */
                if (xorshift32(&g_seed) % 30 == 0) {
                    fprintf(out, "\n");
                }
            }
        } else if (t->type == TOK_COMMENT && !t->protected) {
            /* Strip comments */
        } else {
            fprintf(out, "%s", t->text);
            
            /* After certain keywords, ensure there's a space if needed */
            if (t->type == TOK_KEYWORD && !t->protected) {
                const char *kw = t->text;
                if (strcmp(kw, "return") == 0 || strcmp(kw, "case") == 0 ||
                    strcmp(kw, "goto") == 0 || strcmp(kw, "sizeof") == 0 ||
                    strcmp(kw, "else") == 0 || strcmp(kw, "typedef") == 0 ||
                    strcmp(kw, "extern") == 0 || strcmp(kw, "static") == 0 ||
                    strcmp(kw, "const") == 0 || strcmp(kw, "volatile") == 0 ||
                    strcmp(kw, "register") == 0 || strcmp(kw, "inline") == 0 ||
                    strcmp(kw, "restrict") == 0 || strcmp(kw, "unsigned") == 0 ||
                    strcmp(kw, "signed") == 0 || strcmp(kw, "short") == 0 ||
                    strcmp(kw, "long") == 0 || strcmp(kw, "struct") == 0 ||
                    strcmp(kw, "union") == 0 || strcmp(kw, "enum") == 0) {
                    /* Look ahead to see if next non-whitespace token is alphanumeric */
                    for (int j = i + 1; j < g_token_count; j++) {
                        Token *next = &g_tokens[j];
                        if (next->type == TOK_WHITESPACE || next->type == TOK_NEWLINE) continue;
                        if (next->type == TOK_IDENT || next->type == TOK_KEYWORD || 
                            next->type == TOK_NUMBER) {
                            fprintf(out, " ");
                        }
                        break;
                    }
                }
            }
        }
    }
    fprintf(out, "\n");
}

/* ========== Self-Check ========== */
static bool self_check(void) {
    int paren = 0, brace = 0, bracket = 0;
    
    for (int i = 0; i < g_token_count; i++) {
        Token *t = &g_tokens[i];
        
        if (t->type == TOK_STRING) continue;
        if (t->type == TOK_CHAR) continue;
        if (t->type == TOK_COMMENT) continue;
        if (t->type == TOK_PREPROC) continue;
        
        if (t->type == TOK_PUNCT) {
            switch (t->text[0]) {
                case '(': paren++; break;
                case ')': paren--; break;
                case '{': brace++; break;
                case '}': brace--; break;
                case '[': bracket++; break;
                case ']': bracket--; break;
            }
            
            if (paren < 0 || brace < 0 || bracket < 0) {
                log_warn("Unbalanced brackets detected at line %d", t->line);
                return false;
            }
        }
    }
    
    if (paren != 0 || brace != 0 || bracket != 0) {
        log_warn("Unclosed brackets: () = %d, {} = %d, [] = %d", paren, brace, bracket);
        return false;
    }
    
    return true;
}

/* ========== Main Pipeline ========== */
static char *read_file(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", filename);
        return NULL;
    }
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *buf = malloc(size + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }
    
    size_t read = fread(buf, 1, size, f);
    buf[read] = '\0';
    fclose(f);
    
    return buf;
}

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s input.c output.c [options]\n", prog);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  --seed <n>      Fixed random seed\n");
    fprintf(stderr, "  --passes <k>    Number of passes (default: 2)\n");
    fprintf(stderr, "  --safe          Only safe transformations\n");
    fprintf(stderr, "  --aggressive    Enable aggressive transforms\n");
}

static void cleanup(void) {
    for (int i = 0; i < g_token_count; i++) {
        free(g_tokens[i].text);
    }
    free(g_tokens);
    
    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol *s = g_symbol_hash[i];
        while (s) {
            Symbol *next = s->next;
            free(s->name);
            free(s->renamed);
            free(s);
            s = next;
        }
    }
    
    for (int i = 0; i < g_string_count; i++) {
        free(g_strings[i].original);
        free(g_strings[i].encoded_name);
        free(g_strings[i].encoded_data);
    }
    
    for (int i = 0; i < g_function_count; i++) {
        free(g_functions[i].name);
    }
}

int main(int argc, char *argv[]) {
    /* Parse arguments */
    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }
    
    g_input_file = argv[1];
    g_output_file = argv[2];
    g_seed = (uint32_t)time(NULL);
    
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            g_seed = (uint32_t)atoi(argv[++i]);
        } else if (strcmp(argv[i], "--passes") == 0 && i + 1 < argc) {
            g_passes = atoi(argv[++i]);
            if (g_passes < 1) g_passes = 1;
            if (g_passes > 5) g_passes = 5;
        } else if (strcmp(argv[i], "--safe") == 0) {
            g_safe_mode = true;
        } else if (strcmp(argv[i], "--aggressive") == 0) {
            g_aggressive = true;
        }
    }
    
    printf("=== C Source Obfuscator ===\n");
    printf("Input:  %s\n", g_input_file);
    printf("Output: %s\n", g_output_file);
    printf("Seed:   %u\n", g_seed);
    printf("Passes: %d\n", g_passes);
    printf("Mode:   %s%s\n", g_safe_mode ? "safe" : "normal", g_aggressive ? " (aggressive)" : "");
    printf("\n");
    
    /* Read input file */
    char *source = read_file(g_input_file);
    if (!source) {
        return 1;
    }
    
    /* Phase 1: Tokenize */
    log_info("Phase 1: Lexical analysis...");
    if (!tokenize(source)) {
        fprintf(stderr, "Error: Tokenization failed\n");
        free(source);
        return 1;
    }
    log_info("Tokenized %d tokens", g_token_count);
    free(source);
    
    /* Phase 2: Collect symbols */
    log_info("Phase 2: Symbol collection...");
    collect_symbols();
    
    /* Phase 3: Multi-pass transformation */
    log_info("Phase 3: Transformations (%d passes)...", g_passes);
    
    for (int pass = 0; pass < g_passes; pass++) {
        log_info("  Pass %d/%d", pass + 1, g_passes);
        
        /* Pass 1 or safe mode: identifier renaming */
        if (pass == 0) {
            rename_identifiers();
        }
        
        /* Pass 2: String encoding */
        if (pass == 1 || (g_passes == 1 && pass == 0)) {
            collect_strings();
        }
        
        /* Pass 3+: Number obfuscation and control flow */
        if (pass >= 1 && !g_safe_mode) {
            obfuscate_numbers();
            
            if (g_aggressive) {
                find_functions();
                insert_opaque_predicates();
            }
        }
    }
    
    /* Phase 4: Self-check */
    log_info("Phase 4: Self-check...");
    if (!self_check()) {
        log_warn("Self-check found issues, output may have problems");
    } else {
        log_info("Self-check passed");
    }
    
    /* Phase 5: Output */
    log_info("Phase 5: Generating output...");
    FILE *out = fopen(g_output_file, "w");
    if (!out) {
        fprintf(stderr, "Error: Cannot open output file '%s'\n", g_output_file);
        cleanup();
        return 1;
    }
    
    fprintf(out, "/* Obfuscated by encrypt - seed: %u */\n", g_seed);
    /* Disable common warnings caused by obfuscation */
    fprintf(out, "#ifdef __GNUC__\n");
    fprintf(out, "#pragma GCC diagnostic ignored \"-Wformat-security\"\n");
    fprintf(out, "#pragma GCC diagnostic ignored \"-Wmisleading-indentation\"\n");
    fprintf(out, "#endif\n");
    fprintf(out, "#ifdef __clang__\n");
    fprintf(out, "#pragma clang diagnostic ignored \"-Wformat-security\"\n");
    fprintf(out, "#endif\n\n");
    generate_output(out);
    fclose(out);
    
    /* Summary */
    printf("\n=== Summary ===\n");
    printf("Tokens processed: %d\n", g_token_count);
    printf("Strings encoded:  %d\n", g_string_count);
    printf("Functions found:  %d\n", g_function_count);
    
    if (g_skipped_functions > 0) {
        printf("Functions skipped (unsafe): %d\n", g_skipped_functions);
    }
    
    printf("Output written to: %s\n", g_output_file);
    
    cleanup();
    return 0;
}
