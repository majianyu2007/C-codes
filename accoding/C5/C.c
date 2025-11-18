#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        long long L;
        if (a == 0) {
            L = 2;
        } else if (a == 1) {
            L = 1;
        } else {
            long long l0 = 2, l1 = 1;
            for (int k = 2; k <= a; ++k) {
                long long t = l0 + l1;
                l0 = l1;
                l1 = t;
            }
            L = l1;
        }
        printf("%lld\n", L);
        }
    return 0;
}