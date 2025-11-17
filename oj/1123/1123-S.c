#include <stdio.h>

int main(void)
{
    int num[10];
    int d1, d2, x1, x2, temp;

    for ( int i = 0; i < 10; i++ )
    {
        scanf("%d", &num[i]);
    }

    d1 = num[0];
    x1 = num[0];
    d2 = 0;
    x2 = 0;

    for ( int j = 1; j < 10; j++ )
    {
        if ( num[j] > d1 )
        {
            d1 = num[j];
            d2 = j;
        }
        else if ( num[j] < x1 )
        {
            x1 = num[j];
            x2 = j;
        }
        else
        {
            continue;
        }
    }
    
    temp = num[0];
    num[0] = num[d2];
    num[d2] = temp;

    if (x2 == 0)
        x2 = d2;

    temp = num[9];
    num[9] = num[x2];
    num[x2] = temp;

    for ( int k = 0; k < 10; k++ )
    {
        printf("%d ", num[k]);
    }
    printf("\n");
    return 0;
}



