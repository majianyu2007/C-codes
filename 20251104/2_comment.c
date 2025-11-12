#include <stdio.h>

// 函数声明
int ProcessData(int);       // 声明值传递函数（处理数据并返回结果）
void UpdateValues(int *, int *);  // 声明地址传递函数（通过指针修改外部变量）
void UpdateValuesFail(int, int);  // 声明值传递函数（尝试修改但无法影响外部变量）

int main() {
    int a = 10, b = 20;
    int result = 0;

    result = ProcessData(a);  // 将a的值（10）传入，接收返回值（15）
    ProcessData(b);           // 将b的值（20）传入，返回值（25）未使用
    printf("First: a=%d, b=%d, result=%d\n", a, b, result);  // a和b仍为初始值

    UpdateValues(&a, &b/* 传入a和b的地址，允许函数修改原变量 */);
    printf("Second: a=%d, b=%d\n", a, b);  // a和b已被修改

    UpdateValuesFail(a, b/* 传入当前a和b的值，函数内修改不影响外部 */);
    printf("Third: a=%d, b=%d\n", a, b);  // a和b保持修改后的值（未受影响）

    return 0;
}

int ProcessData(int num)  // num是传入参数的副本（如a的副本为10）
{
    int result;
    result = num + 5;     // 仅修改函数内，不影响原变量（如a仍为10）
    return result;        // 返回处理后的结果
}

void UpdateValues(int *t1, int *t2)  // t1指向a的地址，t2指向b的地址
{
    *t1 += 5;  // 通过指针解引用（*t1）直接修改a的实际值（a = a + 5）
    *t2 += 10; // 通过指针解引用（*t2）直接修改b的实际值（b = b + 10）
}

void UpdateValuesFail(int t1, int t2)  // t1是a的副本，t2是b的副本
{
    t1 += 5;   // 仅修改函数内t1，原变量a不受影响
    t2 += 10;  // 仅修改函数内t2，原变量b不受影响
}
