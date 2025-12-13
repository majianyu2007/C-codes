#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int count = 0;
    long long sum = 0;
    
    for (int i = N; i >= 1 && count < M; i--) {
        if (i % 13 == 0 || i % 17 == 0) {
            sum += i;
            count++;
        }
    }
    
    printf("%lld\n", sum);
    
    return 0;
}