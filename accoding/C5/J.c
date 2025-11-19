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
    if (scanf("%lld", &n) != 1) return 0;

    // 不能直接用题目中的 ((x-1)!+1)/x 判定：
    // 1) 溢出：对 long long 而言 (x-1)! 在 x>20 时就溢出，结果失真；
    // 2) 复杂度：即便改为按模 x 逐步相乘避免溢出，每个 x 仍需 O(x) 次乘法，
    //    总体 O(n^2) 级别，容易超时；
    // 3) 依据威尔逊定理：当 x>=2 时，上式为整数当且仅当 x 为素数。
    //    因此直接做素数判定更稳妥高效。x=1 单独处理。

    for (long long x = 1; x <= n; ++x) {
        if (x == 1) { // ((0)!+1)/1 == 2，为整数
            count++;
            continue;
        }
        int is_prime = 1;
        if (x % 2 == 0) {
            is_prime = (x == 2);
        } else {
            for (long long d = 3; d * d <= x; d += 2) {
                if (x % d == 0) { is_prime = 0; break; }
            }
        }
        if (is_prime) count++;
    }

    printf("%lld\n", count);
    return 0;
}