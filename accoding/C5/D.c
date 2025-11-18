#include <stdio.h>
#include <stdbool.h>

static bool is_prime(long long x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (long long i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

static long long next_prime(long long n) {
    if (n <= 2) return 2;
    long long c = n;
    if ((c & 1LL) == 0) c++; // make odd
    while (!is_prime(c)) c += 2;
    return c;
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        long long n;
        if (scanf("%lld", &n) != 1) return 0;
        printf("%lld\n", next_prime(n));
    }
    return 0;
}