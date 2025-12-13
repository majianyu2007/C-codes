#include <stdio.h>

int SumArray1(int n, int a[n]); // 正确，先定义n再定义a[n]
                                // 实际上它叫做变长数组
                                //  1.声明前可设定长度
                                //  2.但声明后长度无法改变
//int SumArray2(int a[n], int n);   // 错误！n未定义
//int SumArray5(int, int a[n]);     // 错误！n未定义
int SumArray3(int n, int a[*]); // 正确
int SumArray4(int, int [*]);    // 正确
int SumArray5(int, int *);      // 正确

int main()
{
    int size = 10;
    int arr1[10] = {[5] = 9, [9] = 5};
//    int arr2[size] = {[5] = 9, [9] = 5}; // 有可能与大括号初始化冲突
    int arr3[10] = {8,9};
//    int arr4[size] = {8,9};
    int arr5[size];
    for(int i = 0; i < size; i++)
    {
        arr5[i] = 0;
    }
    arr5[5] = 9;
    arr5[9] = 5;
    printf("SumArray1: %d\n", SumArray1(size, arr1));
    printf("SumArray3: %d\n", SumArray3(size, arr3));
    printf("SumArray4: %d\n", SumArray4(size, arr5));
    printf("SumArray5: %d\n", SumArray5(size, arr5));
    return 0;
}

int SumArray1(int n, int a[n])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

int SumArray3(int n, int a[])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

int SumArray4(int n, int a[])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

int SumArray5(int n, int *a)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}
