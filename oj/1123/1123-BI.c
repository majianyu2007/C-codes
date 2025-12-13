#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPSILON 1e-6

double BiRoot(double (*fun)(double), double a, double b);

double f1(double x) {
    return x * x * x - 10 * x * x + 3 * x + 20.0;
}

double f2(double x) {
    return x * x * x - 6 * x - 1;
}

int main(void) {
    double a, b;
    int choice;
    
    printf("Select function (1 or 2): ");
    scanf("%d", &choice);
    
    printf("Enter a: ");
    scanf("%lf", &a);
    
    printf("Enter b: ");
    scanf("%lf", &b);
    
    double result;
    if (choice == 1) {
        result = BiRoot(f1, a, b);
    } else {
        result = BiRoot(f2, a, b);
    }
    
    printf("%.3f\n", result);
    
    return 0;
}

double BiRoot(double (*fun)(double), double a, double b) {
    double fa = fun(a);
    double fb = fun(b);
    
    if (fa * fb > 0) {
        printf("error! a,b have the same sign.\n");
        exit(1);
    }
    
    double mid, fmid;
    
    while (1) {
        mid = (a + b) / 2.0;
        fmid = fun(mid);
        
        if (fabs(fmid) < EPSILON) {
            return mid;
        }
        
        if (fa * fmid < 0) {
            b = mid;
            fb = fmid;
        } else {
            a = mid;
            fa = fmid;
        }
    }
}