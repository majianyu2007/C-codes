#include <stdio.h>
#include <math.h>

int main(void)
{
    double min = 0, max = 0, temp = 0, sum = 0, mean = 0;
    int i;
    for ( i = 0 ; i <= 200 ; i++ )
    {
        scanf("%lf", &temp);
        if (fabs(temp + 1.0) < 1e-6) break;

        if ( i == 0 ) {
            min = max = temp;
        } else {
            if (temp > max) max = temp;
            if (temp < min) min = temp;
        }
        sum += temp;
    }
    mean = ( sum - max - min ) / ( i - 2 );
    printf("%.2lf\n", mean);
    return 0;
}

