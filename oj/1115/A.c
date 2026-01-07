#include <stdio.h>

int process(int, int, int); 

int main(void)
{
    int n = 0, x = 0;
    if ((scanf("%d", &n)) != 1) return -1;
    if (n < 1 || n > 32) printf("Invalid number\n");
    x = process(1, n, 1);
    printf("%d\n", x);
    return 0;
}

int process(int m, int n, int x)
{
    if (m == n) return x;
    return (process(m + 1, n, x) + 1) * 2;
}

