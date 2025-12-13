#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6

void Swap(int *, int *); //交换两个整型元素
void Shuffle(int [], int); // 随机打乱数组（无需关注）
void PrintArr(int [], int); // 打印数组（上一段代码已实现过）
void BubbleSort(int [], int); // 冒泡排序（上节课已实现过）
void SelectionSort(int [], int); // 选择排序
void InsertSort(int [], int); // 插入排序
int BiSearch(int [], int, int); // 二分查找

int main(void)
{
    srand(time(NULL)); // 时间随机种子（无需关注）

    int test_count = 0;
    int arr[N] = {1, 2, 3, 4, 5, 6};

    // 冒泡排序
    printf("Test %d\n", ++test_count);
    Shuffle(arr, N);
    printf("Shuffled: ");
    PrintArr(arr, N);
    BubbleSort(arr, N);
    printf("BubbleSort: ");
    PrintArr(arr, N);
    printf("\n");

    // 选择排序
    printf("Test %d\n", ++test_count);
    Shuffle(arr, N);
    printf("Shuffled: ");
    PrintArr(arr, N);
    SelectionSort(arr, N);
    printf("SelectionSort: ");
    PrintArr(arr, N);
    printf("\n");
    
    // 插入排序
    printf("Test %d\n", ++test_count);
    Shuffle(arr, N);
    printf("Shuffled: ");
    PrintArr(arr, N);
    InsertSort(arr, N);
    printf("InsertSort: ");
    PrintArr(arr, N);
    printf("\n");

    // 二分查找（要基于有序数组）
    printf("Test %d\n", ++test_count);
    PrintArr(arr, N);
    int toFind = 4;
    printf("The index of %d is %d\n", toFind, BiSearch(arr, N, toFind));
    toFind = 20;
    printf("The index of %d is %d\n", toFind, BiSearch(arr, N, toFind));
    printf("\n");
    
    return 0;
}

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Shuffle(int arr[], int n)
{
    for(int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Swap(&arr[i], &arr[j]);
    }
}

void PrintArr(int arr[], int n)
{
    for(int i = 0;i < n - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[n-1]);
}

void BubbleSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void SelectionSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int minInd = i;
        for(int j = i; j < n; j++)
        {
            if(arr[j] < arr[minInd])
            {
                minInd = j;
            }
        }
        if(minInd != i)
        {
            Swap(&arr[minInd], &arr[i]);
        }
    }
}

void InsertSort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int t = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > t)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}

int BiSearch(int arr[], int n, int key)
{
    int left = 0;
    int right = n - 1;
    while(left <= right)
    {
        int mid = (left + right) / 2;
        if(key == arr[mid])
        {
            return mid;
        }
        else if(key > arr[mid])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;



}



