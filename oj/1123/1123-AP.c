#include <stdio.h>
#include <string.h>

int main() {
    char str[25];
    unsigned char font;
    FILE *fp;
    int i, j, k, len;

   fgets(str, sizeof(str), stdin);
    len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[--len] = '\0';
    }

    fp = fopen("ASC10x8.dic", "rb");
    if (fp == NULL)
        return 1;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < len; j++)
        {
            int offset = (str[j] - 0x20) * 10 + i;
            fseek(fp, offset, SEEK_SET);
            fread(&font, 1, 1, fp);

            for (k = 7; k >= 0; k--)
            {
                if (font & (1 << k))
                    putchar('#');
                else
                    putchar(' ');
            }
        }
        putchar('\n');
    }

    fclose(fp);
    return 0;
}
