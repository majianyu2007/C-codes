#include <stdio.h>
#include <math.h>

double dis(double x1, double y1, double z1, double x2, double y2, double z2);

int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        double arr[9];
        for (int j = 0; j < 9; j++) 
        {
            scanf("%lf", &arr[j]);
        }

        double AB = dis(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
        double BC = dis(arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);
        double AC = dis(arr[0], arr[1], arr[2], arr[6], arr[7], arr[8]);
        
        double cos_angle = (AB*AB + BC*BC - AC*AC) / (2.0 * AB * BC);
        double angle = acos(cos_angle);
        printf("%.5lf\n", angle);
    }
    return 0;
}



double dis(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double result;
    result = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2));
    return result;
}