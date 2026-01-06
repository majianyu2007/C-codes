#include <stdio.h>
#include <string.h>

#define MAX_SEQ_LEN 80

int rle(char *code, const char *seq);
int readSeq(char *seq, int n);

int main()
{
    char seq[MAX_SEQ_LEN + 1] = { 0 };
    char code[2 * MAX_SEQ_LEN + 1];
    char *p = NULL;
    int r;

    readSeq(seq, MAX_SEQ_LEN);
    if (strcmp(seq, "NULL"))
        r = rle(code, seq);
    else
        r = rle(code, p);
    switch (r) {
    case 0:
        printf("%s\n", code);
        break;
    case -1:
        printf("Length is inValid.\n");
        break;
    case -2:
        printf("Has inValid character.\n");
        break;
    }
    return 0;
}

int readSeq(char *seq, int n)
{
    int ch, k;
    k = 0;

    while ((ch = getchar())) {
        if (ch == '\n' || ch == '\r' || ch == EOF)
            break;
        seq[k++] = ch;
    }

    seq[k] = '\0';
    return k;
}

int rle(char *code, const char *seq)
{
    int i, len = 0;
    char *p;

    if (seq == NULL)
        return -1;
    p = (char *)seq;
    len = 0;
    while (*p != '\0') {
        char token = *p;
        i = 1;
        token &= 0xDF;
        if (token > 'Z' || token < 'A')
            return -2;
        while (token == (*(++p) & 0xDF)) {
            i++;
        }
        len = sprintf(code, "%d%c", i, token);
        code += len;
    }
    *code = '\0';
    return 0;
}
