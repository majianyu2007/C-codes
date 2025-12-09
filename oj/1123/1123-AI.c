#include <stdio.h>

int isSymmetric(int matrix[4][4]) 
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            if (matrix[i][j] != matrix[j][i]) 
            {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int matrix[4][4];
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    if (isSymmetric(matrix)) 
    {
        printf("Yes\n");
    } 
    else 
    {
        printf("No\n");
    }
    
    return 0;
}