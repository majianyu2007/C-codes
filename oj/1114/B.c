#include <stdio.h>
#include <stdlib.h>

int Create(int ***, int, int);
int Input(int **, int, int);
int Find(int **, int, int, int, int *, int *);
int main()
{
    int m, n, t;
    int i, j, r;
    int **a;
    scanf("%d%d%d", &m, &n, &t);
    Create(&a, m, n);
    Input(a, m, n);
    r = Find(a, m, n, t, &i, &j);
    if(r == 0)
    {
        printf("%d\n", r);
    }
    else
    {
        printf("%d %d %d\n", r, i, j);
    }
    return 0;
}
int Create(int ***p, int m, int n)
{
    int i;
    (*p) = (int **)malloc(m * sizeof(int *));
    if(NULL == (*p))
    {
        printf("Not enough row's memory!\n");
        exit(1);
    }
    for (i = 0; i < m; i++)
    {
        (*p)[i] =(int *)malloc(n * sizeof(int));
        if(NULL == (*p)[i])
        {
            printf("Not enough col's memory!\n");
            exit(1);
        }
    }
    return 0;
}

int Input(int **p, int m, int n)
{
    int i, j;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }
    return 0;
}
/****以上代码不能提交****/


int Find(int **arr, int m, int n, int t, int *pi, int *pj)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(arr[i][j] == t)
            {
                *pi = i;
                *pj = j;
                return 1;
            }
        }
    }
    return 0;
}
