#include <stdio.h>

int get_ena13(char *ena);

int main(void)
{
    char ena[13];
    int verify = -1;
    if(fgets(ena, 13, stdin) == NULL ) return -1;
    verify = get_ena13(ena);
    printf("%d", verify);
    return 0;
}

int get_ena13(char *ena)
{
    int r1 = 0xFF, r2 = 0x00, r3 = 0, r4 = 0;
    for(int i = 0; i < 12; i++)
    {

        if (i % 2 == 0)
        {
            r1 = r1 & ena[i];
            continue;
        }
        else
        {
            r2 = r2 | ena[i];
            continue;
        }
    }
    r3 = r1 * 3 + r2;
    if (r3 % 10)
    {
        r4 = ((r3 / 10) + 1) * 10 - r3;
    }
    else
    {
        r4 = (r3 / 10) * 10 - r3;
    }
    return r4;
}


