#include <stdio.h>
#include <math.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    for (int i=0; i<n; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        double result = 0;
        result = pow((double)a, (1.0 / b));
        printf("%.5f\n", result);
    }
    return 0;
}