#include <stdio.h>

int main(void)
{
    float supline,dowline,high,area;
    scanf("%f%*c%f%*c%f", &supline, &dowline, &high);
    area = ((supline+dowline)*high)/2.0;
    printf("%f\n",area);
    return 0;
}
