/*
 * dehead - Expand all #includes to produce a single-file output.
 * Usage: ./dehead input.c output.c [-- cpp_flags...]
 */
#define _GNU_SOURCE  /* for mkstemp, fdopen, getline */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>

#define MAX_ARGS 256

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s input.c output.c [-- cpp_flags...]\n", prog);
    fprintf(stderr, "Expand all #includes to produce a single-file output.\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  --          Separator; subsequent args are passed to preprocessor\n");
    fprintf(stderr, "\nEnvironment:\n");
    fprintf(stderr, "  CC          C compiler to use (default: cc)\n");
    exit(2);
}

/* Check if line is a preprocessor line marker (# <num> "file" or #line <num>) */
static int is_line_marker(const char *line) {
    if (line[0] != '#') return 0;

    const char *p = line + 1;
    /* Skip whitespace after # */
    while (*p == ' ' || *p == '\t') p++;

    /* Case 1: # <digit>... "filename" [flags] */
    if (isdigit((unsigned char)*p)) {
        return 1;
    }

    /* Case 2: #line <digit>... */
    if (strncmp(p, "line", 4) == 0 && (p[4] == ' ' || p[4] == '\t')) {
        p += 4;
        while (*p == ' ' || *p == '\t') p++;
        if (isdigit((unsigned char)*p)) {
            return 1;
        }
    }

    return 0;
}

/* Generate temporary filename in same directory as target */
static char *make_temp_path(const char *output) {
    size_t len = strlen(output);
    char *tmp = malloc(len + 8);  /* .XXXXXX + \0 */
    if (!tmp) return NULL;
    snprintf(tmp, len + 8, "%s.XXXXXX", output);
    return tmp;
}

int main(int argc, char *argv[]) {
    const char *cc;
    const char *input;
    const char *output;
    char *cpp_args[MAX_ARGS];
    int idx = 0;
    int cpp_flags_start = -1;  /* -1 means no -- found */
    char *tmp_path = NULL;
    FILE *outfile = NULL;
    FILE *pipein = NULL;
    int pipefd[2] = {-1, -1};
    pid_t pid = -1;
    int ret = 1;
    char *line = NULL;
    size_t line_cap = 0;

    /* --- Argument parsing --- */
    if (argc < 3) {
        usage(argv[0]);
    }

    input = argv[1];
    output = argv[2];

    /* Find -- separator */
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--") == 0) {
            cpp_flags_start = i + 1;
            break;
        }
    }

    /* If there are extra args but no --, that's an error */
    if (argc > 3 && cpp_flags_start < 0) {
        fprintf(stderr, "Error: unexpected argument '%s'\n", argv[3]);
        fprintf(stderr, "Use '--' before preprocessor flags.\n");
        usage(argv[0]);
    }

    /* --- Get compiler from environment --- */
    cc = getenv("CC");
    if (!cc || *cc == '\0') {
        cc = "cc";
    }

    /* --- Build preprocessor command --- */
    cpp_args[idx++] = (char *)cc;
    cpp_args[idx++] = "-E";
    cpp_args[idx++] = "-P";  /* Suppress line markers */

    /* Add user-provided flags after -- */
    if (cpp_flags_start > 0) {
        for (int i = cpp_flags_start; i < argc; i++) {
            if (idx >= MAX_ARGS - 2) {  /* Reserve space for input + NULL */
                fprintf(stderr, "Error: too many preprocessor flags (max %d args)\n",
                        MAX_ARGS - 4);
                return 1;
            }
            cpp_args[idx++] = argv[i];
        }
    }

    cpp_args[idx++] = (char *)input;
    cpp_args[idx] = NULL;

    /* --- Create temporary output file --- */
    tmp_path = make_temp_path(output);
    if (!tmp_path) {
        perror("Error allocating temp path");
        return 1;
    }

    int tmp_fd = mkstemp(tmp_path);
    if (tmp_fd < 0) {
        perror("Error creating temp file");
        free(tmp_path);
        return 1;
    }

    outfile = fdopen(tmp_fd, "w");
    if (!outfile) {
        perror("Error opening temp file for writing");
        close(tmp_fd);
        unlink(tmp_path);
        free(tmp_path);
        return 1;
    }

    /* --- Create pipe for capturing preprocessor output --- */
    if (pipe(pipefd) == -1) {
        perror("Error creating pipe");
        goto cleanup;
    }

    /* --- Fork and exec preprocessor --- */
    pid = fork();
    if (pid == -1) {
        perror("Error forking");
        goto cleanup;
    }

    if (pid == 0) {
        /* Child: run preprocessor */
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            _exit(127);
        }
        close(pipefd[1]);

        execvp(cc, cpp_args);
        fprintf(stderr, "Error executing '%s': %s\n", cc, strerror(errno));
        _exit(127);
    }

    /* Parent: read preprocessor output */
    close(pipefd[1]);
    pipefd[1] = -1;

    pipein = fdopen(pipefd[0], "r");
    if (!pipein) {
        perror("Error opening pipe for reading");
        goto cleanup;
    }
    pipefd[0] = -1;  /* Now owned by pipein */

    /* --- Filter output: remove line markers, keep everything else --- */
    ssize_t nread;
    while ((nread = getline(&line, &line_cap, pipein)) != -1) {
        /* Skip line markers (fallback filter if -P didn't remove all) */
        if (is_line_marker(line)) {
            continue;
        }
        if (fputs(line, outfile) == EOF) {
            perror("Error writing to output");
            goto cleanup;
        }
    }

    if (ferror(pipein)) {
        perror("Error reading from preprocessor");
        goto cleanup;
    }

    free(line);
    line = NULL;
    fclose(pipein);
    pipein = NULL;

    if (fclose(outfile) != 0) {
        perror("Error closing output file");
        outfile = NULL;
        goto cleanup;
    }
    outfile = NULL;

    /* --- Wait for child and check exit status --- */
    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("Error waiting for preprocessor");
        goto cleanup;
    }
    pid = -1;

    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        if (exit_code != 0) {
            fprintf(stderr, "Error: preprocessor '%s' failed with exit code %d\n",
                    cc, exit_code);
            goto cleanup;
        }
    } else if (WIFSIGNALED(status)) {
        fprintf(stderr, "Error: preprocessor '%s' killed by signal %d\n",
                cc, WTERMSIG(status));
        goto cleanup;
    }

    /* --- Success: atomically rename temp file to output --- */
    if (rename(tmp_path, output) != 0) {
        perror("Error renaming temp file to output");
        goto cleanup;
    }

    free(tmp_path);
    return 0;

cleanup:
    /* Clean up on failure */
    free(line);
    if (pipein) fclose(pipein);
    if (pipefd[0] >= 0) close(pipefd[0]);
    if (pipefd[1] >= 0) close(pipefd[1]);
    if (outfile) fclose(outfile);
    if (tmp_path) {
        unlink(tmp_path);
        free(tmp_path);
    }
    /* If child is still running, wait for it */
    if (pid > 0) {
        waitpid(pid, NULL, 0);
    }
    return ret;
}
