#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    if (gcd(a, b) == 1) {
        printf("Yes.\n");
    } else {
        printf("No.\n");
    }
    
    return 0;
}