#include <stdio.h>

int Sum_Septenary(int n);
int Is_Prime(int n);

int main(void)
{
    int dec = 0, result = -1;
    scanf("%d", &dec);
    result = Is_Prime(dec);
    printf("%d\n", result);
    return 0;
}

/***
int Sum_Septenary(int n)
{
    int result = 0;
    int process = n;
    if (process > 7)
    {
        while(process)
        {
            result += process % 7;
            process = process / 7;
        }
    }
    else
    {
        return process;
    }
    return result;
}
***/

int Sum_Septenary(int n) {
    int result = 0;
    int process = n;
    while (process) {
        result += process % 7;
        process = process / 7;
    }
    return result;
}

int Is_Prime(int n)
{
    for( int i = 2; i < n; i++ )
    {
        if ( n % i == 0 )
        {
            return 0;
        }
    }
    return 1;
}

/***
int Is_Prime(int n)
{
    int process = n, sum7=0;
    if ( n == 0 ) return 0;
    sum7 = Sum_Septenary(process);
    
check:    if ( sum7 > 0 && sum7 <= 7 )
    {
        switch (sum7) {
            case 1: case 5: case 7: return 1;
            case 4: case 2: case 6: case 3: case 0: return 0;
            default: break;
        }
    }
    else
    {
        sum7 = Sum_Septenary(process);
        goto check;
    }
***/
    
    
    /***
    while(1)
    {
        switch (sum7) {
            case 1: case 5: case 7: return 1;
            case 4: case 2: case 6: case 3: case 0: return 0;                
            default: sum7 = Sum_Septenary(process);
                     break;
        }
    }
     ***/
