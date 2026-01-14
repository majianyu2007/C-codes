#include <stdio.h>

char evaBMI(double w, double h);

int main(void)
{
    double w, h;

    scanf("%lf%*c%lf", &w, &h);
    printf("%c\n", evaBMI(w, h));
    return 0;
}

char evaBMI(double w, double h)
{
    double b;
    if ( w > 0 && h > 0 )
    {
        b = w / ( h * h );
        if ( b < 18.5 )
        {
            return 'S';
        }
        if ( b >= 18.5 && b < 24.0 )
        {
            return 'N';
        }
        if ( b >= 24.0 && b < 28.0 )
        {
            return 'O';
        }
        if ( b >= 28.0 )
        {
            return 'F';
        }
    }
    else
    {
        return 'E';
    }
}


