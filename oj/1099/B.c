#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int m = 0, n = 0;
    if ((scanf("%d %d",&m, &n)) != 2) return 1;

    char **mat;
    mat = NULL;
    mat = (char **)malloc(m * sizeof(char *));
    for(int i = 0; i < m; i++)
    {
        mat[i] = (char *)malloc(n * sizeof(char));
    }

    int where = 0, count = 0;
    int maxr = m - 1, maxc = n - 1, minr = 0, minc = 0;
    int i = 0, j = 0;
row:
    if(j == minc)  // 向右填充
    {
        for(; j <= maxc; j++)
        {
            mat[i][j] = (char)('A' + where++);
            if (where == 26) where = 0;
            count++;
        }
        j--;      // 回到最后有效位置
        minr++;   // 上边界下移
        i++;      // 准备向下
        if(count == m * n) goto next;
        goto column;
    }
    else  // 向左填充
    {
        for(; j >= minc; j--)
        {
            mat[i][j] = (char)('A' + where++);
            if (where == 26) where = 0;
            count++;
        }
        j++;      // 回到最后有效位置
        maxr--;   // 下边界上移
        i--;      // 准备向上
        if(count == m * n) goto next;
        goto column;
    }

column:
    if(i <= maxr && j == maxc)  // 向下填充
    {
        for(; i <= maxr; i++)
        {
            mat[i][j] = (char)('A' + where++);
            if (where == 26) where = 0;
            count++;
        }
        i--;      // 回到最后有效位置
        maxc--;   // 右边界左移
        j--;      // 准备向左
        if(count == m * n) goto next;
        goto row;
    }
    else  // 向上填充
    {
        for(; i >= minr; i--)
        {
            mat[i][j] = (char)('A' + where++);
            if (where == 26) where = 0;
            count++;
        }
        i++;      // 回到最后有效位置
        minc++;   // 左边界右移
        j++;      // 准备向右
        if(count == m * n) goto next;
        goto row;
    }

next:
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j == n - 1)
            {
                printf("%c", mat[i][j]);
            }
            else
            {
                printf("%c ", mat[i][j]);
            }
        }
        printf("\n");
    }

    for(int i = 0; i < m; i++)
    {
        free(mat[i]);
    }
    free(mat);

    return 0;
}
