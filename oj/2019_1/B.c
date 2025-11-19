#include <stdio.h>

int main(void)
{
    int a, b;
    if ((scanf("%d/%d", &a, &b)) != 2 || b == 0)
    {
        printf("Invalid input\n");
        return 1;
    }

    if (a >= 10 && a < b && b < 100)
    {
        // Vaild Input !
    }
    else
    {        
        printf("Invalid input\n");
        return 1;    
    }

    printf("0.");

    for (int i = 0; i < 200; i++)
    {
        a *= 10;
        int digit = a / b;
        printf("%d", digit);
        a = a % b;
    }
    printf("\n");
    return 0;
}