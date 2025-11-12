#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    printf("请输入一个整数: ");
    scanf("%d", &num);
    
    if (isPrime(num)) {
        printf("%d 是素数\n", num);
    } else {
        printf("%d 不是素数\n", num);
    }
    
    return 0;
}

// 线性筛法（欧拉筛法）- 在 O(n) 时间内筛出所有素数
void linearSieve(int n) {
    bool *is_prime = (bool *)malloc((n + 1) * sizeof(bool));
    int *primes = (int *)malloc((n + 1) * sizeof(int));
    int cnt = 0;
    
    for (int i = 0; i <= n; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * primes[j] <= n; j++) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;  // 关键：保证每个合数只被其最小质因子筛掉
            }
        }
    }
    
    printf("\n%d 以内的所有素数：\n", n);
    for (int i = 0; i < cnt; i++) {
        printf("%d ", primes[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n共有 %d 个素数\n", cnt);
    
    free(is_prime);
    free(primes);
}