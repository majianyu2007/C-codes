#include <stdio.h>
#include <math.h>

/* 非线性函数原型 */
double f (double x);

/* 二分求解函数原型 */
double BinarySearch(double,double);

int main ()
{
    double x, a, b;

    scanf("%lf%lf", &a,&b);
    if(f(a)*f(b)>0)     /* 此处填空 */
    {
        printf("错误,a和b同号!\n");
        return 0; /* 由于O系统原因，返回0值。 */
    }
    x=BinarySearch(a, b);  /* 此处填空 */
    printf("%5.3f\n",x);
    return 0;
}
double f (double x)
{
    return x*x*x-10*x*x+3*x+20.0;
}

double BinarySearch (double a,double b)
{
    double x;

    x=(a+b)/2.0;
    if(fabs(f(x))<1e-6)   /* 此处填空 */
    return x;
    else
    {
    if(f(a)*f(x)>0)
        return BinarySearch(x, b);    /* 此处填空 */
    else
        return BinarySearch(a, x);    /* 此处填空 */
    }
}