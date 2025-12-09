#include <stdio.h>
#include <stdlib.h>

int** TransMat(int** matrix, int m, int n) 
{
    int **arr;
    arr = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        arr[i] = (int *)malloc(m * sizeof(int));
        if(arr[i] == NULL)
            return NULL;
        for(int j = 0; j < m; j++) {
            arr[i][j] = matrix[j][i];
        }
    }
    return arr;
}

int main() {
    int n;
    scanf("%d", &n);
    int **matrix = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) 
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int **transposed = TransMat(matrix, n, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < n; i++) {
        free(transposed[i]);
    }
    free(transposed);
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}