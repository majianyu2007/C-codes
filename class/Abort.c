#include <stdio.h>
#include <stdlib.h>

void AbortSuc();
void AbortZero();
void AbortFail();

int main()
{
    char ch = getchar();
    int *p;
    switch(ch)
    {
        case '0':
            AbortZero();
        case '1':
            AbortSuc();
        case '2':
            AbortFail();
        case '3':
            exit(-1);
        case 'e':
            *p = 42;
            return 0;
        default:
            return 0;
    }
}

void AbortSuc()
{
    exit(EXIT_SUCCESS);
}

void AbortZero()
{
    exit(0);
}

void AbortFail()
{
    exit(EXIT_FAILURE);
}
