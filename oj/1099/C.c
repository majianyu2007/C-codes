#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char str[256];

    fgets(str, sizeof(str), stdin);
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        str[i] = (char)toupper((unsigned char)str[i]);
    }

    int new_word = 1;

    char fstr[256] = {0};

    int k = 0;

    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (!isspace((unsigned char)str[i]) &&
            (i == 0 || isspace((unsigned char)str[i - 1])))
        {
            if (k < (int)sizeof(fstr) - 1)
                fstr[k++] = str[i];
        }
    }
    fstr[k] = '\0';

    if (strstr(str, fstr))
    {
        printf("Y\n");
    }
    else
    {
        printf("N\n");
    }

    return 0;
}
