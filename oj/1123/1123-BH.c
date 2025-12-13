#include <stdio.h>

/* 判断整数n是否素数，是返回1，否则返回0 */
int isprime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

/* 分解偶数n，返回值为分解结果中最小的素数 */
int resolve(int n) {
    for (int i = 2; i <= n / 2; i++) {
        if (isprime(i) && isprime(n - i)) {
            return i;
        }
    }
    return 0;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    for (int i = m; i <= n; i++) {
        if (i > 2 && i % 2 == 0) {
            int p = resolve(i);
            printf("%d=%d+%d\n", i, p, i - p);
        }
    }
    
    return 0;
}