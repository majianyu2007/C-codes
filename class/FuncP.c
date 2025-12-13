#include <stdio.h>
#include <stdlib.h>

void Swap(int *, int *);
void PrintArr(int [], int);

void Func(){}
int JudgeMore(int, int); // 判断前数是否比后数大
int JudgeLess(int, int); // 判断前数是否比后数小
void BubbleSort(int [], int, int (*)(int, int));
int Cmp(const void *, const void *); // 用于qsort

int main()
{
    int sect_count = 0;

    // 1. 用debug查看函数名的本质
    printf("%d. 用debug查看函数名的本质\n", ++sect_count);
    void (*p)() = Func;
    printf("\n");

//    // 2. 声明和调用指针形式的函数
//    printf("%d. 声明和调用指针形式的函数\n", ++sect_count);
//    p = JudgeMore; // 函数指针与被指向函数的类型必须一致
//    int (*pm)(int, int);
//    pm = JudgeMore;
//    printf("函数JudgeMore的函数段起始地址是%p\n", JudgeMore);
//    printf("函数指针pm目前指向的地址是%p\n", pm);
//
//    int m = (*pm)(5, 20);
//    printf("5比20大的真假判断结果是: %d\n", m);
//    int (*pl)(int, int) = JudgeLess;
//    printf("5比20小的真假判断结果是: %d\n", (*pl)(5, 20));
//    printf("\n");

//    // 3. 函数指针作为函数参数
//    printf("%d. 函数指针作为函数参数\n", ++sect_count);
//    int arr[] = {5, 6, 4, 8, 9, 1, 7, 10, 0, 8};
//    BubbleSort(arr, 10, JudgeLess); // 降序排列
//    PrintArr(arr, 10);
//    BubbleSort(arr, 10, JudgeMore); // 升序排列
//    PrintArr(arr, 10);
//    printf("\n");

//    // 4. 函数指针作为参数的应用
//    printf("%d. 函数指针用于系统函数排序qsort\n", ++sect_count);
//    qsort(arr, 10, sizeof(int), Cmp);
//    PrintArr(arr, 10);
//    printf("\n");
    
    return 0;
}

void Swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void PrintArr(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[n - 1]);
}

int JudgeMore(int a, int b)
{
    return a > b;
}

int JudgeLess(int a, int b)
{
    return a < b;
}


