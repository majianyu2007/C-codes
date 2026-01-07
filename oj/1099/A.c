#include <stdio.h>

int main() {
    int N;
    long long M;
    if (scanf("%d %lld", &N, &M) != 2) return 0;

    long long res = 0;
    for (int i = 2; i <= N; i++) {
        res = (res + M) % i;
    }

    printf("%lld\n", res + 1);
    return 0;
}
