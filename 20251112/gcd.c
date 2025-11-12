#include <stdio.h>

// 异或交换函数
void Swap(int *a, int *b) {
    if (a != b && *a != *b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

// 递归方式的 gcd
int gcd_recursive(int a, int b) {
    if (a < b) {
        Swap(&a, &b);
    }
    if (b == 0) {
        return a;
    }
    return gcd_recursive(b, a % b);
}

// 迭代方式的 gcd
int gcd_iterative(int a, int b) {
    if (a < b) {
        Swap(&a, &b);
    }
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 使用三元运算符的递归 gcd
int gcd_ternary(int a, int b) {
    if (a < b) {
        Swap(&a, &b);
    }
    return (b == 0) ? a : gcd_ternary(b, a % b);
}

int main() {
    int num1, num2;
    
    printf("请输入两个正整数: ");
    scanf("%d %d", &num1, &num2);
    
    printf("\n使用递归方式: gcd(%d, %d) = %d\n", num1, num2, gcd_recursive(num1, num2));
    printf("使用迭代方式: gcd(%d, %d) = %d\n", num1, num2, gcd_iterative(num1, num2));
    printf("使用三元运算符: gcd(%d, %d) = %d\n", num1, num2, gcd_ternary(num1, num2));
    
    return 0;
}