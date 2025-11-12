#include <stdio.h>

int main(void)
{
    int A, B, C, max; //声明变量
    scanf("%d%*c%d%*c%d", &A, &B, &C); //输入
    max = A > B ? (A > C ? A : C) : (B > C ? B : C); 
    // 比大小
    // 先判断 A 和 B 的大小；
    // 如果 A > B，则进一步比较 A 和 C，将较大值赋给 max
    // 如果 A ≤ B，则进一步比较 B 和 C，将较大值赋给 max
    printf("The maximum of A=%d, B=%d, C=%d is %d.\n", A, B, C, max);
    return 0;
}

