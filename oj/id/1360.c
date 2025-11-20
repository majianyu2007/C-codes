#include <stdio.h>

int main(void)
{
    int n, sum = 0;
    if ((scanf("%d", &n)) != 1 || n < 1 || n > 10000) printf("invalid number\n");
    for (int i = 1; i * i < n; i++)
    {
        if ( i % 2 == 0 ) continue;
        sum += i * i;
    }
    printf("sum=%d\n", sum);
    return 0;
}

