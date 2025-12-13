#include <stdio.h>
#include <stdlib.h>

void PrintDyn2DArr(int, int, int **);

int **CreateMat(int, int);
void CreateTimesTab(int ***);
void FreeDyn2DIntArr(int **, int);

/* 课后为大家补充了如下函数以进行输出检验 */
void PrintTimesTab(int **);

int main()
{
    int sect_count = 1;
    // 1. 为什么要使用动态二维数组(举例说明)

    // 2. 用动态二维数组存储m*n的整型矩阵
    printf("%d. m乘n的动态二维数组\n", ++sect_count);
    int **mat = CreateMat(5, 6);
    mat[0][0] = 5;
    mat[4][5] = 6;
    printf("%d %d\n", mat[0][0], mat[4][5]);
    PrintDyn2DArr(5, 6, mat);
    printf("\n");

    // 3. 用动态二维数组存储99乘法表
    printf("%d. 存储99乘法表\n", ++sect_count);
    int **timesTab;
    CreateTimesTab(&timesTab);
    PrintTimesTab(timesTab);
    printf("\n");

    // 4. 销毁动态二维数组
    printf("%d. 销毁动态数组\n", ++sect_count);
    FreeDyn2DIntArr(mat, 5);
    FreeDyn2DIntArr(timesTab, 9);
    printf("\n");

    return 0;
}


int **CreateMat(int m, int n)
{
    int **arr;
    arr = (int **)malloc(m * sizeof(int *));
    for(int i = 0; i < m; i++)
    {
        arr[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++)
        {
            arr[i][j] = 0;
        }
    }
    return arr;
}

void PrintDyn2DArr(int m, int n, int **arr)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
           printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void CreateTimesTab(int ***tp)
{
    int **times;
    times = (int **)malloc(9 * sizeof(int *));
    for(int i = 0; i < 9; i++)
    {
        times[i] = (int *)malloc((i + 1) * sizeof(int));
        for(int j = 0; j < i + 1; j++) 
        /* 课上由于测试不完善，没有发现表达式2应到i结束，此处已修改 */
        {
            times[i][j] = (i + 1) * (j + 1);
        }
    }
    *tp = times;
}

void FreeDyn2DIntArr(int **arr, int m)
{
    for(int i = 0; i < m; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

/* OJ上打印杨辉三角的题目也应采用动态分配的思路 */
void PrintTimesTab(int **tt)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < i; j++)
        {
            printf("%d ", tt[i][j]);
        }
        printf("%d\n", tt[i][i]);
    }
    printf("\n");
}
