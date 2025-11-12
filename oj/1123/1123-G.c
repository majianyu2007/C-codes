#include <stdio.h>

int main(void)
{
    char ch;
    int verify;

    ch = getchar();
    verify = ch;

    if ( verify >= 65 && verify <= 90 ){
        verify = verify + 32;
        ch = verify;
    } else if ( verify >= 97 && verify <= 122 ){
        verify = verify - 32;
        ch = verify;
    } else {
        ch = ch;
    }
    printf("%c\n", ch);
    return 0;
}
