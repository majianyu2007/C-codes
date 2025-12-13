#include <stdio.h>

int Fact(int); // 递归计算n的阶乘
int Fibonacci(int); // 递归求解n阶斐波那契数列i
int Pow(int m, int n); // 递归求解m的n次方

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d的阶乘: %d\n", n, Fact(n));
    printf("斐波纳契数列的第%d项: %d\n", n, Fibonacci(n));

    return 0;
}
