#include <stdio.h>

int main(void)
{
    int a = 0;
    int i = 0;

    while (1)
    {
        a += 1;
        i += 1;

        if ( i == 6 )
        {
            break;
        }
    }
    printf("%d\n", a);
    return 0;
}

