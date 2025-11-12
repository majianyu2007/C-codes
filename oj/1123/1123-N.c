#include <stdio.h>

int main(void)
{
    int a, b, oa, ob, rem, Div, Multi;
    scanf("%d%*c%d", &a, &b);
    oa = a;
    ob = b;
    do {
        rem = a % b;
        a = b;
        b = rem;
    }while( rem != 0 );

    Div = a;
    Multi = oa * ob / Div;
    printf("%d\n%d\n", Div, Multi);
    return 0;
}

