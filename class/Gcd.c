#include <stdio.h>

void Swap(int *, int*);
int Gcd_f(int, int);
int Gcd(int, int);
int Gcd_r(int, int);

int main(void)
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d %d %d\n", Gcd_f(a, b), Gcd(a, b), Gcd_r(a, b));
    return 0;
}


void Swap(int *a, int*b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int Gcd_f(int a, int b)
{
    int r = a < b ? a : b;
    for(; r > 1; r--)
    {
        if(a % r == 0 && b % r == 0)
        {
            break;
        }
    }
    return r;
}

int Gcd(int a, int b)
{
    if(a < b)
    {
        Swap(&a, &b);
    }
    
    int r;
    while(b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int Gcd_r(int a, int b)
{
    if(a < b)
    {
        Swap(&a, &b);
    }

    if(b == 0)
    {
        return a;
    }

    Gcd_r(b, a % b);
}





