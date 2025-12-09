#include <stdio.h>

int gcd(int m, int n) {
    int rem;
    while (n != 0) 
    {
        rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));
    return 0;
}