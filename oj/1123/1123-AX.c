#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n >= 0) {
        printf("P,");
    } else {
        printf("N,");
        n = -n;
    }
    
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    
    printf("%d\n", sum);
    
    return 0;
}