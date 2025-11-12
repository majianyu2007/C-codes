#include <stdio.h>
#include <math.h>

void Trans(int, int, char[]);

int main(void)
{
    int n, to;
    char str[3];
    
    scanf("%d%*c%d", &n, &to);

    Trans(n, to, str);

    printf("%s\n", str);

    return 0;
}

void Trans(int a, int b, char str[])
{
    if( a > pow(2, b))
    {
        str[0] = '0';
        str[1] = '0';
        str[2] = '\0';
        return;
    }

    str[2] = '\0';
    str[1] = a % b + '0';
    a /= b;
    str[0] = a % b + '0';
    return;
}

