#include "myfunc.h"

void PrintIntArr(int arr[], int len)
{
    for(int i = 0; i < len - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[len - 1]);
}
