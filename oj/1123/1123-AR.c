#include <stdio.h>

int containsEight(int n) 
{
    while (n > 0) 
    {
        if (n % 10 == 8) 
        {
            return 1;
        }
        n /= 10;
    }
    return 0;
}

int main() 
{
    int a, b, count = 0;
    scanf("%d %d", &a, &b);
    
    for (int i = a; i <= b; i++) 
    {
        if (containsEight(i)) 
        {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}