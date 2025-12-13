#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 定义精度常量（误差阈值）
#define EPSILON 1e-10

// 定义 π 常量
const double pi = 3.1415926;

// 子函数：使用泰勒级数计算 sin(x)
double GetSinx(double);

// 主函数
int main() {
    printf("sin(pi/2) = %.15f\n", sin(pi / 2));
    printf("GetSinx(pi/2) = %.15f\n", GetSinx(pi / 2));

    printf("\nsin(pi/3) = %.15f\n", sin(pi / 3));
    printf("GetSinx(pi/3) = %.15f\n", GetSinx(pi / 3));

    printf("\n误差分析：\n");
    printf("pi/2 误差: %.2e\n", fabs(sin(pi / 2) - GetSinx(pi / 2)));
    printf("pi/3 误差: %.2e\n", fabs(sin(pi / 3) - GetSinx(pi / 3)));

    return 0;
}


double GetSinx(double x) {
    double sum = x;           // 累加和，初始为 x
    double x_pow = x;         // x 的幂（x, x^3, x^5...）
    double item = 0.0;        // 当前项
    int n = 1;                // 指数控制（奇数：1,3,5...）
    long long int fact = 1;   // 阶乘（1!, 3!, 5!...）
    int sign = 1;             // 符号：+1, -1, +1...

    do {
        // 计算阶乘：fact = (n+1)*(n+2) -> 从 (n+1)! 到 (n+2)!
        fact *= (n + 1) * (n + 2);
        // 更新 x 的幂：x^(n+2) = x^n * x^2
        x_pow *= x * x;
        // 更新符号
        sign = -sign;
        // 计算当前项：(-1)^k * x^(2k+1)/(2k+1)!
        item = sign * x_pow / fact;
        // 累加到总和
        sum += item;
        // 下一项指数增加 2
        n += 2;
    } while (fabs(item) > EPSILON);  // 当前项足够小则停止

    return sum;
}
