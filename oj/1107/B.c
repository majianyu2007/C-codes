#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *ConReversal(char *);

int ReadLine(char *s, int max_len)
{
    int i=0, ch;
    while(i < max_len)
    {
        ch = getchar();
        if (ch == EOF || ch == '\n') break;
        s[i++] = ch;
    }
    s[i] = '\0';
    return i;
}

int main()
{
    char s[256] = {0};
    ReadLine(s, 255);
    puts(ConReversal(s));
    return 0;
}

char *ConReversal(char *str)
{
    size_t n = strlen(str);

    for (size_t i = 0; i < n / 2; i++) {
        size_t j = n - 1 - i;

        int ci = isalpha((unsigned char)str[i]);
        int cj = isalpha((unsigned char)str[j]);
        char li = (char)tolower((unsigned char)str[i]);
        char lj = (char)tolower((unsigned char)str[j]);

        int is_con_i = ci && !(li=='a' || li=='e' || li=='i' || li=='o' || li=='u');
        int is_con_j = cj && !(lj=='a' || lj=='e' || lj=='i' || lj=='o' || lj=='u');

        if (is_con_i && is_con_j) {
            char tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
        }
    }
    return str;
}

