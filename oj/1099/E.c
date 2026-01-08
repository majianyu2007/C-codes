#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1024

char* revSentenceWords(char *, const char *, const char *);
char** splitSentenceWords(char *, const char *, size_t);
char isSentence(const char *, const char *);
size_t getWordsCnt(const char *, const char *);

int ReadLine(char *, int);

int ReadLine(char *str, int len)
{
    int n = 0, ch = 0;
    while((ch = getchar()) != EOF && ch != '\n' && n < len - 1)
        str[n++] = ch;
    str[n]='\0';
    return n;
}

int main(void)
{
    char s[MAXLENGTH];
    char *p,**q;
    char delim[] = " \t\n\r";
    char term[] = ".?!";
    char hyphen[] = " ";
    int i, wc = 0;

    ReadLine(s, MAXLENGTH);
    if (isSentence(s, term))
    {
        p = revSentenceWords(s, delim, hyphen);
        puts(p);
        wc = getWordsCnt(p, delim);
        printf("WordsCnt= %d\n", wc);
        q = splitSentenceWords(p, delim, wc);
        for(i = 0; i < wc; i++)
        {
            puts(q[i]);
        }
        free(q);
        free(p);
    }
    return(0);
}

char isSentence(const char *s, const char *term)
{
    char terminator = 0;
    size_t len = 0;

    len = strlen(s);
    terminator = s[len - 1];

    if(!strchr(term, terminator))
    {
        printf("Sentence needs a terminating character. (./?/!)\n\n");
        exit(0);
    }

    return terminator;
}

size_t getWordsCnt(const char *s, const char *delim)
{
    size_t cnt = 0;

    while(*s)
    {
        if((!strchr(delim, *s) && (strchr(delim, *(s + 1)))) || (*(s + 1) == '\0' && (!strchr(delim, *s))))
        {
            cnt++;
        }
        s++;
    }
    return cnt;
}


char ** splitSentenceWords(char *str , const char *delim, size_t n)
{
    if(n == 0) return NULL;
    char **q = (char **)malloc(sizeof(char *) * n);
    if(!q) return NULL;

    char *p = str;
    size_t i = 0;

    while(i < n)
    {
        while(*p && strchr(delim, *p)) p++;
        q[i++] = p;
        while(*p && !strchr(delim, *p)) p++;
        if(*p)
        {
            *p = '\0';
            p++;
        }
    }
    return q;
}

char * revSentenceWords(char *str, const char *delim, const char *hyphen)
{
    size_t len = strlen(str);
    char terminator = str[len - 1];

    size_t bodylen = (len > 0) ? (len - 1) : 0;
    char *tmp = (char *)malloc(bodylen + 1);
    if(!tmp) return NULL;
    if(bodylen) memcpy(tmp, str, bodylen);
    tmp[bodylen] = '\0';

    size_t wc = getWordsCnt(tmp, delim);
    if(wc == 0)
    {
        char *out0 = (char *)malloc(2);
        if(!out0) { free(tmp); return NULL; }
        out0[0] = terminator;
        out0[1] = '\0';
        free(tmp);
        return out0;
    }

    char **words = splitSentenceWords(tmp, delim, wc);
    if(!words)
    {
        free(tmp); return NULL;
    }

    size_t hylen = strlen(hyphen);
    size_t total = 2 + hylen * (wc - 1);
    for(size_t i = 0; i < wc; i++)
    {
        total += strlen(words[i]);
    }

    char *out = (char *)malloc(total);
    if(!out)
    {
        free(words);
        free(tmp);
        return NULL;
    }

    char *dst = out;
    for(size_t i = wc; i-- > 0;)
    {
        size_t wlen = strlen(words[i]);
        memcpy(dst, words[i], wlen);
        dst += wlen;
        if(i > 0)
        {
            memcpy(dst, hyphen, hylen);
            dst += hylen;
        }
    }
    *dst++ = terminator;
    *dst = '\0';

    free(words);
    free(tmp);
    return out;
}
