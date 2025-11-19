#include <stdio.h>
#include <math.h>

long long factorial(long long x)
{
    long long result = 1;
    for (long long i = 2; i <= x; i++)
    {
        result *= i;
    }
    return result;
}

int main(void)
{
    long long n, count = 0;
    scanf("%lld", &n);
    for (long long i = 1; i<=n; i++)
    {
        double process = ( factorial(i-1) + 1 ) / i;
        if (fabs(process - (int)process) < 1e-9)
        {
            count++;
        }
    }
    printf("%lld\n", count);
    return 0;
}