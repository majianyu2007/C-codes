#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f1(double);
double df1(double);
double f2(double);
double df2(double);
double f3(double);
double df3(double);
double Newton(double (*fun)(double), double (*dfun)(double), double x0);

 int main() 
{ 
      double x0;
       int n; 

      scanf("%d%lf",&n,&x0); 
      switch(n) 
      { 
      case 1: 
              printf("%.5f\n", Newton(f1,df1,x0)); 
              break; 
      case 2: 
              printf("%.5f\n", Newton(f2,df2,x0)); 
              break; 
      case 3: 
              printf("%.5f\n", Newton(f3,df3,x0)); 
              break; 
      default: 
              printf("error1\n"); 
              exit(0); 
      } 
      return 0; 
} 

double f1(double x) { 
      return x*x*x-10*x*x+3*x+20.0; 
} 

double df1(double x) { 
      return 3*x*x-20*x+3; 
}

double f2(double x) { 
      return x*x*x-6*x-1; 
}

double df2(double x) { 
      return 3*x*x-6; 
}

double f3(double x) { 
      return x*x*x+10*x-20; 
}

double df3(double x) { 
      return 3*x*x+10; 
}


double Newton (double (*fun)(double), double (*dfun)(double),double x0)
{
    double x1 = x0 - fun(x0)/dfun(x0);
    while (!(fabs(x1 - x0) < 1e-5)) 
    {
        x0 = x1;
        x1 = x0 - fun(x0)/dfun(x0);
    }
    return x1;
}
