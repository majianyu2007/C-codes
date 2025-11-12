#include <stdio.h>

int main(void)
{
    int n = 0, a = 0, b = 0, suma = 0, sumb = 0, t = 0;
    scanf("%d", &n);
    for ( int i = 0; i < n ; i++){
        scanf("%d", &t);
        if ( t % 2 == 0 ){
            b++;
            sumb = sumb + t;
            t = 0;
        }else{
            a++;
            suma = suma + t;
            t = 0;
        }
    }
    printf("%d\n%d\n%d\n%d\n", suma, a, sumb, b);
    return 0;
}

