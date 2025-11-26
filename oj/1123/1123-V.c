#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 0;
    scanf("%d", &n);
    int **arr;
    arr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc((i + 1) * sizeof(int));
    }
    for (int i = 0; i < n; i++)
    {
        arr[i][0] = 1;
        arr[i][i] = 1;
        for (int j = 0; j < i; j++)
        {
            if ( j == 0 ) continue;
            arr[i][j]=arr[i-1][j-1]+ arr[i-1][j];
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < k + 1; l++)
        {
            printf("%d ", arr[k][l]);
        }
        printf("\n");
    }
    for (int m = 0; m < n; m++)
    {
        free(arr[m]);
    }
    free(arr);
    return 0;
}

