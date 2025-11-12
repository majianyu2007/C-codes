#include <stdio.h>

int main(void)
{
    float a, b, c;
    scanf("%f%*c%f%*c%f", &a, &b ,&c);

    if ( a + b > c && b + c > a && c + a > b )
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
