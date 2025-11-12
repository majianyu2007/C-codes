#include <stdio.h>
int main(void) 
{
    int x = 5, y = 0, z = 1, result;
    printf("Initial values: x=%d, y=%d, z=%d\n", x, y, z);// 初始值由int声明时赋予
    // 计算 x > 3，将结果赋给 result
    result = ( x > 3 );
    // printf 打印输出
    printf("After x > 3: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // x > 3 为真，5 > 3，故result为真（1）
    // 计算 y == 0，将结果赋给 result
    result = ( y == 0 );
    // printf 打印输出
    printf("After y == 0: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // y == 0 为真，0 == 0，故result为真（1）
    // 计算 z != 1，将结果赋给 result
    result = ( z != 1 );
    // printf 输出
    printf("After z != 0: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // z != 0 为假，z == 0，故result为假（0）
    // 计算 x > 3 && y == 0，将结果赋给 result
    result = ( x > 3 && y == 0 );
    // printf 打印输出
    printf("After x > 3 && y == 0: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // &&是逻辑与运算符，要求两边同时为真。变量x的值大于3，且变量y的值等于0，左右两个条件同时满足，所以逻辑与运算的结果为真（1）
    // 计算 x > 3 && z != 1，将结果赋给 result
    result = ( x > 3 && z != 1 );
    // printf 打印输出
    printf("After x > 3 && z != 1: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // &&是逻辑与运算符，要求两边同时为真。变量x的值大于3，且变量z的值不等于1，前一条件满足，后一条件不满足，所以逻辑与运算的结果为假（0）
    // 计算 x <= 3 || y == 0，将结果赋给 result
    result = ( x <= 3 || y == 0 );
    // printf 打印输出
    printf("After x <= 3 || y == 0: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // ||是逻辑或运算符，要求有一为真即可为真。变量x的值小于等于3，或y的值为0，后者满足条件，所以逻辑或运算的结果为真（1）
    // 计算 !y，将结果赋给 result
    result = ( !y );
    // printf 打印输出
    printf("After !y: result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // !为逻辑非运算符，y的值为0为非，取反后为真，所以逻辑非运算的结果为真（1）
    // 计算 !(x > 3 && y == 0)，将结果赋给 result
    result = ( !(x > 3 && y == 0) );
    // printf 打印输出
    printf("After !(x > 3 && y == 0): result=%d, x=%d, y=%d, z=%d\n", result, x, y, z);
    // 括号在这里用于改变（提高）运算优先级，先执行括号内部的逻辑表达式 x > 3 && y == 0
    // 如果没有括号，逻辑非运算符 ! 的优先级高于 &&，会先计算 !x，再与后续表达式进行运算，将会完全改变表达式的逻辑含义，导致结果错误
    // !为逻辑非运算符，用于对其后的布尔值（或可转换为布尔值的表达式）进行取反操作，这里对表达式的计算结果进行取反
    // 根据上一步语句可知，括号内的表达式 x > 3 && y == 0 的结果为 1（真）
    // 因此 !(x > 3 && y == 0) 等价于 !1，逻辑非运算的结果为 0（假）
    // 所以此处的 result 变量被赋值为 0
    printf("Final values: x=%d, y=%d, z=%d, result=%d\n", x, y, z, result);
    // 本题目仅对result的值进行了改变，且输出结果前未再次对result进行操作
    return 0;
}
