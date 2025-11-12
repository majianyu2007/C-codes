#include <stdio.h>

int main(void)
{
    int x = 1, n = 0;
    scanf("%d", &n);
    for ( int i=1; i < n; i++){
        x = 2 * ( x + 1 );
    }
    printf("%d\n", x);
    return 0;
}
