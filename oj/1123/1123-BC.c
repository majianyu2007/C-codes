#include <stdio.h>
#include <stdlib.h>

void ex_num(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void exchange(int a[], int n)
{
    int left, right;
    int cnt;

    left = 0;
    right = n - 1;
    cnt = 1;
    while (left < right)
    {
        if (!(a[left] & 1) && (a[right] & 1)) {
             printf("Times %d: %d<==>%d\n", cnt++, a[left], a[right]);
             ex_num(&a[left], &a[right]);
        }
        left = (a[left] & 1) ? left+1 : left;
        right = !(a[right] & 1) ? right-1 : right;
    }
    return;
}

int main()
{
    int  *arr, sz;
    int i;

    scanf("%d", &sz);
    arr=(int *)malloc(sz * sizeof(int));
    if (arr==NULL) return 0;
    for (i = 0; i < sz; i++)  {
        scanf("%d", &arr[i]);
    }
    exchange(arr, sz);
    for (i = 0; i < sz; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]); 
    }
    printf("\n");
    free(arr);
    return 0;
}
