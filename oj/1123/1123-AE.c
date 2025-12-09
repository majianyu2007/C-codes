#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) 
    {
        return 0;
    }
    int *arr = (int *)malloc(sizeof(int) * n);
    if (!arr) 
    {
        return NULL;
    }
    for (int i = 0; i < n; ++i) 
    {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), cmp);

    for (int i = 0; i < n; ++i) 
    {
        if (i) 
        {
            putchar(' ');
        }
        printf("%d", arr[i]);
    }
    putchar('\n');
    free(arr);
    return 0;
}