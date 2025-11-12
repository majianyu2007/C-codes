#include <stdio.h>

int main(void)
{
    float mark;
    scanf("%f", &mark);
    if ( mark < 60 )
        printf("Fail\n");
    else
        printf("Pass\n");
    return 0;
}
