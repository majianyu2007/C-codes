#include <stdio.h>
#include <math.h>
double getSum(int m, int n ); /* 函数声明 */
void readdouble(double *d);

int main( )
{
    double sum;
    int m, n;

    scanf("%d%d", &m, &n);
    sum = getSum( m, n);
    printf("%.8f\n", sum);
    return 0;
}

void readdouble(double *d)
{
    double t=-1.0;
    int r = 0;

    while(r != 1 && r != EOF)  {
        r=scanf("%lf",&t);
    }
    *d = (r == EOF)? *d: t;
}

double getSum(int m, int n )
{
    double sum = 0.0;
    int count = 0;
    int readcount = 0;
    
    while(readcount < m && count < n)
    {
        double d = 0.0;
        readdouble(&d);
        readcount++;
        
        if (fabs(d - (-1.0)) < 1e-9)
        {
            break;
        }
        
        if (fabs(d) > 1e-9 && fabs(d - 4.0) > 1e-9 && d > 0.0 && d < 4.0)
        {
            sum += d;
            count++;
        }
    }
    
    return sum;
}
