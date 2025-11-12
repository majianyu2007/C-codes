#include <stdio.h>

int main(void)
{
    float a, b;
    scanf("%f%*c%f", &a,&b);
    printf("和=%f,差=%f,积=%f,商=%f\n", a+b, a-b, a*b, a/b);
    return 0;
}
