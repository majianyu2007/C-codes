#include <stdio.h>

int main(void)
{
    char ch;
    int line;

    ch = getchar();
    getchar();
    scanf("%d", &line);

    for ( int i = 1; i <= line; i++ ){
        for ( int j = 0; j < ( line - i ); j++){
            printf(" ");
        }

        for ( int k = 0; k < ( 2 * i - 1 ) ; k++ ){
            printf("%c", ch);
        }
        printf("\n");
    }

    return 0;
}


