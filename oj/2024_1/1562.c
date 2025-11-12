#include <stdio.h>

int isValidPasswd(const char *pw, int n);

int main(void)
{
    int n;
    char pw[n];
    
    scanf("%d", &n);
    scanf("%s", pw);

    return isValidPasswd(pw, n);
}

int isValidPasswd(const char *pw, int n)
{
    int flag1=0, flag2=0, flag3=0, flag4=0;

    for ( int i = 0; i < n; i++)
    {
        if ( 'a' <= pw[i] && pw[i] <= 'z' ) 
        {
            flag1 = 1;
            continue;
        }
        else if ( 'A' <= pw[i] && pw[i] <= 'Z' )
        {
            flag2 = 2;
            continue;
        }
        else if ( '0' <= pw[i] && pw[i] <= '9' ) 
        {
            flag3 = 4;
            continue;
        }
        else
        {
            flag4 = 8;
            continue;
        }
    }
    return (15-(flag1+flag2+flag3+flag4));
}

