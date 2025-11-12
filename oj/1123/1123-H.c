#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, c, d, area;
    
    scanf("%f%f%f",&a,&b,&c);

    if ( a + b > c && b + c > a && c + a > b ){
        d = ( a + b + c ) * 0.5;
        area = sqrt(d * ( d - a ) * ( d - b ) * ( d - c ));
        printf("三角形的面积是:%f\n",area);
    } else
        printf("这3个数无法组成三角形!\n");
    return 0;
}
