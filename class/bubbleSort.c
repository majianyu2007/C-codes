#include <stdio.h>

void bubbleSort(int *, int);
void Swap(int *, int *);

int main()
{
    int arr[6] = {1, 2, 3, 4, 5, 6};
    bubbleSort(arr, 6);
    for(int i = 0; i < 6; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int *arr, int len)
{
    for(int i = 0; i < len - 1; i++)
    {
        for(int j = 0; j < len - i - 1; j++)
        {
            if(arr[j] < arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
