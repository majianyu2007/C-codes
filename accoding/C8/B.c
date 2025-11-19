#include <stdio.h>

void BubbleSort(long long arr[], long long n);
void Swap(long long *a, long long *b);

int main(void)
{
    long long n;
    scanf("%lld", &n);
    long long arr[n];
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }
    BubbleSort(arr, n);
    for (long long j = 0; j < n; j++)
    {
        if ( j < n - 1 )
        {
            if (arr[j] != -1)
            {
                printf("%lld ", arr[j]);
            }
        }
        else
        {
            if (arr[j] != -1)
            {
                printf("%lld\n", arr[j]);
            }
        }
    }
    return 0;
}

void BubbleSort(long long arr[], long long n)
{
    for(long long i = 0; i < n - 1; i++)
    {
        for(long long j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
            }
            else if(arr[j] == arr[j + 1])
            {
                arr[j] = -1;
            }
        }
    }
}

void Swap(long long *a, long long *b)
{
    long long tmp = *a;
    *a = *b;
    *b = tmp;
}
