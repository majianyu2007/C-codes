#include <stdio.h>

void share (int *, int);
void inputArray(int *, int);
void outputArray(int *, int);
void shareCandy(int *, int *, int *);

int main()
{
    int n;
    
    scanf("%d", &n);
    if (n < 3) return 0;

    int Candy[n];
    inputArray(Candy, n);
    share(Candy, n);
    outputArray(Candy, n);

    return 0;
}

void inputArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
}

void outputArray(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n - 1]);
}

/* 以上代码禁止修改和提交 */

void share(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        if (i == 0)
            shareCandy(&a[i], &a[i+1], &a[n-1]);
        else if (i == n - 1)
            shareCandy(&a[i], &a[i-1], &a[0]);
        else
            shareCandy(&a[i], &a[i-1], &a[i+1]);
    }
}

void shareCandy(int *x, int *y, int *z)
{
    *x /= 3;
    *y += *x;
    *z += *x;
}
