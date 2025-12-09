#include <stdio.h>

int isPrime(int n, int m) 
{
    if (n < 2) return 0;
    if (m * m > n) return 1;
    if (n % m == 0) return 0;
    return isPrime(n, m + 1);
}

void findPrimes(int current, int end, int *count) {
    if (current > end) 
    {
        return;
    }

    if (isPrime(current, 2)) 
    {
        printf("%d ", current);
        (*count)++;
    }
    
    findPrimes(current + 1, end, count);
}

int main() 
{
    int a, b;
    scanf("%d %d", &a, &b);
    
    int count = 0;
    findPrimes(a, b, &count);
    printf("\n%d\n", count);
    
    return 0;
}