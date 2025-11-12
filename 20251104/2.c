#include <stdio.h>

// 函数声明
int ProcessData(int);
void UpdateValues(int *, int *);
void UpdateValuesFail(int, int);

int main() {
    int a = 10, b = 20;
    int result = 0;
    
    // ProcessData
    result = ProcessData(a);
    ProcessData(b);
    printf("First: a=%d, b=%d, result=%d\n", a, b, result);

    // UpdateValues
    UpdateValues(&a, &b/* 希望通过处理改变a和b的值 */);
    printf("Second: a=%d, b=%d\n", a, b);

    // UpdateValuesFail
    UpdateValuesFail(a, b/* 希望将a和b的值代入进行处理 */);
    printf("Third: a=%d, b=%d\n", a, b);

    return 0;
}

int ProcessData(int num)
{
    int result;
    result = num + 5;
    return result;
}

void UpdateValues(int *t1, int *t2)
{
    *t1 += 5;
    *t2 += 10;
}

void UpdateValuesFail(int t1, int t2)
{
    t1 += 5;
    t2 += 10;
}

