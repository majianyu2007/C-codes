#include <stdio.h>
#include <stdlib.h> // 动态分配使用的头文件

#define N 5

void PrintArr(int *, int); // 输出数组
void OrderArr(int *, int); // 将数组置为1到n的整数

//int *ReturnAutoArr(int);       // 通过返回值回传auto数组
int *ReturnDynArr1(int);         // 通过返回值回传动态数组
void ReturnDynArr2(int **, int); // 通过参数回传动态数组

int main()
{
    int op_count = 0;

    // 指针的指向
    int *p1;
    int *p2;            // 此时p1, p2为野指针
    p1 = NULL;          // 此时p1为空指针，与野指针不同
    double *p3 = NULL;
    char *p4 = NULL;

    // 动态内存管理函数
    // 1. 动态分配新的内存
    printf("Test %d: Allocate memories\n", ++op_count);
    p1 = (int *)malloc(N * sizeof(int));    // 分配N个元素，值随机
    OrderArr(p1, N);
    PrintArr(p1, N);
    p2 = (int *)calloc(N + 1, sizeof(int)); // 分配N+1个元素，值全为0
    PrintArr(p2, N + 1);
    printf("\n");
    
    // 2. 追加分配内存
    printf("Test %d: Enlarge array\n", ++op_count);
    printf("p1[N]: %d\n", p1[N]); // 数组越界！查看了不属于数组的内存！
    p1[N] = 6; // 越界且不知修改了什么值，危险！危险！危险！
    p1 = (int *)realloc(p1, 1 * sizeof(int)); // 追加分配1个长度
                                              // 若失败则返回NULL
    PrintArr(p1, N + 1); // 以危险操作验证了追加分配时保留了原来的内存
    *(p1 + N) = 7; // 已不越界
    PrintArr(p1, N + 1);
    printf("\n");
    
    // 3. 获取函数中的数组
    printf("Test %d: Get array from functions\n", ++op_count);
//    int *r1 = ReturnAutoArr(N);
//    PrintArr(r1, N);
    int *r2 = ReturnDynArr1(N);
    PrintArr(r2, N);
    int *r3;
    ReturnDynArr2(&r3, N);
    PrintArr(r3, N);
    printf("\n");
    
    // 4. 释放内存
    printf("Test %d: free memories\n", ++op_count);
    free(p1);
    free(p2);
    free(p3); // 意义不大
    free(p4); // 意义不大
    free(r2);
    free(r3); // 再将它们都置为NULL可防止悬空指针
    PrintArr(r3, N);
    printf("\n");
    
    return 0;
}


void PrintArr(int *arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[n - 1]);
}

void OrderArr(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
}

//int *ReturnAutoArr(int n)
//{
//    int a[n];
//    OrderArr(a, n);
//    PrintArr(a, n);
//    return a;
//}

int *ReturnDynArr1(int n)
{
    int *p = (int *)malloc(n * sizeof(int));
    OrderArr(p, n);
    PrintArr(p, n);
    return p;
}

void ReturnDynArr2(int **ap, int n)
{
    int *p = (int *)malloc(n * sizeof(int));
    OrderArr(p, n);
    PrintArr(p, n);
    *ap = p;
}



