#include <stdio.h>

int main(void)
{
    int temp = 0;
    while(scanf("%d", &temp))
    {
        if(temp == -1) break;
        int n = temp / 10;
        int k = temp % 10;
        int s = n - 5 * k;
        printf("%d,%d", temp, s);
        if(!(s % 17))
        {
            printf(",Yes\n");
        }
        else
        {
            printf(",No\n");
        }
    }

    return 0;
}

