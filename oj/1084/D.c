#include <stdio.h >
#include <stdlib.h>
#include <string.h>

#define N 64

int ConvertEmoji(char **dst, const char *src);

int main()
{
    char str[N], *p = NULL;
    int len, i = 0;
    
    fgets(str, N, stdin);
    while(i < strlen(str)) {
        if (str[i]=='\n') { 
            str[i]='\0';
            break;
        }
        i++;
    }
    len=ConvertEmoji(&p, str);
    printf("(%d)%s\n", len, p);
    free(p);
    return 0;
}

int ConvertEmoji(char **dst, const char *src)
{
    const char *emoji_s = "^_^";
    const char *emoji_f = "@_@";
    const char *emoji_c = "T_T";
    const char *emoji_z = "^_~";

    size_t need = 0;

    for(size_t i = 0; src[i] != '\0'; i++)
    {
        if(src[i] == '\\' && src[i + 1] != '\0')
        {
            switch(src[i + 1])
            {
                case 's': need += strlen(emoji_s); i++; continue;
                case 'f': need += strlen(emoji_f); i++; continue;
                case 'c': need += strlen(emoji_c); i++; continue;
                case 'z': need += strlen(emoji_z); i++; continue;
                default: break;
            }
        }
        need++;
    }

    char *out = (char *)malloc(need + 1);
    if(out == NULL)
    {
        return 0;
    }

    size_t w = 0;
    for(size_t i = 0; src[i] != '\0'; i++)
    {
        const char *rep = NULL;
        if(src[i] == '\\' && src[i + 1] != '\0')
        {
            switch(src[i + 1])
            {
                case 's': rep = emoji_s; break;
                case 'f': rep = emoji_f; break;
                case 'c': rep = emoji_c; break;
                case 'z': rep = emoji_z; break;
                default: break;
            }
        }

        if(rep != NULL)
        {
            size_t rlen = strlen(rep);
            memcpy(out + w, rep, rlen);
            w += rlen;
            i++;
        }
        else
        {
            out[w++] = src[i];
        }
    }

    out[w] = '\0';
    *dst = out;

    return (int)w;
}

