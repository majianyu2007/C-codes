#include<stdio.h>

void ScanArr(int [],int); // 输入数组
void PrintArr(int [],int); // 输出输入
void SetArr2Zero(int [],int); // 数组置0
void SetArr2One(int [],int); // 用指针将数组置1
int SumArr(int *,int); // 数组求和（参数为指针形式）

int main()
{
    int op_count = 0;

    // 数组的初始化：大括号初始化
    int arr1[10]={1,0,2,0,3,0,4,0,5,0};
    int arr2[]={1,0,2,0,3,0,4,0,5,0};
    int arr3[10]={1,0,2,0,3,0,4,0,5 /*此处自动补0*/ };
    int arr4[10]={0}; /*清0*/
//    int error[9]={1,0,2,0,3,0,4,0,5,0};
//    int error[11]={};
    int arr5[10]={[0]=1,[2]=2,[4]=3,[6]=4,[8]=5};
    int arr6[10]={1,0,2,[4]=3,0,4,0,[8]=5,0};

    // 输出数组
    printf("操作 %d\n",++op_count);
    PrintArr(arr1,10);
    PrintArr(arr2,10);
    PrintArr(arr3,10);
    PrintArr(arr4,10);
    PrintArr(arr5,10);
    PrintArr(arr6,10);
    printf("\n");

    // 将arr1重新输入并输出
    printf("操作 %d\n",++op_count);
    ScanArr(arr1,10);
    PrintArr(arr1,10);
    printf("\n");

    // 将arr2和arr3清零并输出
    printf("操作 %d\n",++op_count);
    //arr2={0};
    SetArr2Zero(arr2,10);
    PrintArr(arr2,10);
    SetArr2Zero(arr3,10);
    PrintArr(arr3,10);
    printf("\n");

    // 将arr4用指针形式全部置1
    printf("操作 %d\n",++op_count);
    SetArr2One(arr4,10);
    PrintArr(arr4,10);
    printf("\n");

    // 打印arr5的长度并求arr5各元素的和
    printf("操作 %d\n",++op_count);
    printf("Length of arr5: %d\n",(int)(sizeof(arr5)/sizeof(arr5[0])));
    printf("Sum of arr5: %d\n",SumArr(arr5,10));
    printf("\n");

    return 0;
}

void PrintArr(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[n - 1]);
}

void ScanArr(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void SetArr2Zero(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        arr[i] = 0;
    }
}

void SetArr2One(int arr[], int n)
{
    for(int *p = arr; p < arr + n; p++)
    {
        *p = 1;
    }
}

int SumArr(int *arr, int n)
{
    printf("%d\n", (int)(sizeof(arr) / sizeof(arr[0])));
    int r = 0;
    for(int i = 0; i < n; i++)
    {
        r += arr[i];
    }
    return r;
}




