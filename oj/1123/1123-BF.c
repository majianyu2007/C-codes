#include <stdio.h>
#include <stdlib.h>

/* 计算最大公约数（图2） */
int getGCD(int m, int n)
{
    int rem = n;

    while (rem != 0)
    {
        rem = m % n;
        m = n;
        n = rem;
    }

    return m;
}

/* 约分函数（图1） */
int getLowestTerms(int m, int n, int *pNum, int *pDenom)
{
    int gcd;
    int msign = 1, nsign = 1;
    int numsign;

    /* 分子为 0 */
    if (m == 0)
    {
        return 0;
    }

    /* 分子等于分母 */
    if (m == n)
    {
        return 1;
    }

    /* 分母为 0 */
    if (n == 0)
    {
        return -1;
    }

    /* 正常约分 */
    msign = 1;
    nsign = 1;

    if (m < 0)
        msign = -1;

    if (n < 0)
        nsign = -1;

    numsign = msign * nsign;

    m = abs(m);
    n = abs(n);

    *pNum = m;
    *pDenom = n;

    gcd = getGCD(m, n);

    *pNum /= gcd;
    *pNum *= numsign;
    *pDenom /= gcd;

    return 2;
}

/* 输出函数 */
void Output(int status, int nNum, int nDenom)
{
    if (status == 0)
    {
        printf("0");
    }
    else if (status == 1)
    {
        printf("1");
    }
    else if (status == -1)
    {
        printf("Error!");
    }
    else if (status == 2)
    {
        if (nDenom == 1)
        {
            printf("%d", nNum);
        }
        else
        {
            printf("%d/%d", nNum, nDenom);
        }
    }
}

/* 主函数（题目一般已给出，这里给完整示例） */
int main()
{
    int m, n;
    int num, denom;
    int status;

    scanf("%d %d", &m, &n);

    status = getLowestTerms(m, n, &num, &denom);
    Output(status, num, denom);

    return 0;
}
