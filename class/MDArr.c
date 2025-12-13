#include<stdio.h>

void Order2DArrByArr(int, int n, double [][n]);
void Print2DArrByAP(int, int n, double (*)[n]);
void Print2DArrByP(int, int, double *);

int main()
{
    int sect_count = 0;
    // 1. 多维数组
    printf("%d. 多维数组\n", ++sect_count);
    double arr1[3][2] = {{1.1, 0.0}, {0.0, 3.3}, {0.0, 4.4}};
    int m = 3, n = 2;
    double arr2[m][n];// = {{1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6}};
    //arr2 = arr1;
    double arr3[3][3] = {[0][0] = 1.0, [1][1] = 1.0, [2][2] = 1.0};
    printf("%.1f\n\t%.1f\n\t\t%.1f\n", arr3[0][0], arr3[1][1], arr3[2][2]);
    printf("\n");

    // 2. 几种写法的区别
    //  arr1, &arr1, arr1[0], &arr1[0], &arr1[0][0]
    printf("%d. 几种写法的区别：用GDB的whatis和print查看\n", ++sect_count);
    printf("\n");

    // 3. 数组地址类型
    printf("%d. 数组地址类型\n", ++sect_count);
    double (*p2d)[2] = arr1; // 这是数组的指针
    double *p1d[2];// = arr1; // 这是指针类型的数组
    double d = 5.2;
    p1d[0] = &d;
    printf("%.1f\n", *p1d[0]);
    printf("%.1f\n\t%.1f\n\t%.1f\n", p2d[0][0], p2d[1][1], p2d[2][1]);
    printf("%.1f\n\t%.1f\n\t%.1f\n", **p2d,
                                     *(*(p2d + 1) + 1),
                                     *(*(p2d + 2) + 1));
    printf("\n");

    // 4. 多维数组的函数参数
    printf("%d. 多维数组的函数参数\n", ++sect_count);
    Order2DArrByArr(3, 3, arr2);
    Print2DArrByAP(3, 3, arr2);
    printf("\n");

    // 5. 一级指针操作二维数组
    printf("%d. 一级指针操作二维数组\n", ++sect_count);
    Print2DArrByP(3, 2, (double *)arr1);
    Print2DArrByP(m, n, (double *)arr2);
    Print2DArrByP(3, 3, (double *)arr3);
    printf("\n");

    return 0;
}

void Order2DArrByArr(int m, int n, double arr[][n])
{
    double c = 1.1;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            arr[i][j] = c;
            c += 1.1;
        }
    }
}

void Print2DArrByAP(int m, int n, double (*p)[n])
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            //printf("%.1f ", p[i][j]);
            printf("%.1f ", *(*(p + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    
}

void Print2DArrByP(int m, int n, double *arr)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%.1f ", *(arr + i * n + j));
        }
        printf("\n");
    }
    printf("\n");

}
