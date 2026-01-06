#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50

float mae(float *, int);
float factor(int);
float score(float, float);

int main()
{
   int i,n;
   float pIC[N]={8.523,7.678,7.638,7.854,8.387,7.229,4.649,6.983,7.145,6.457,
                 7.174,5.99,7.854, 7.244,7.131,7.319,7.932,6.198,6.39,8.357,
                 6.833,6.368,5.33,5.947,6.71,5.983,6.213,5.785,5.466,5.664,
                 5.206,5.29,5.225,5.324,5.544,7.097,6.658,5,5.921,6.409,7.018,
                 5.745,6.119,5.959,7.051,5.951,6.086,5.712,6.097,7.699},
        MAE,score1,h;

   scanf("%d",&n);
   MAE=mae(pIC,n);
   h=factor(n);
   score1 = score(MAE,h);
   printf("%.2f,%.2f\n",MAE,score1);      
   return 0;
}

float mae(float pIC[],int n)
{
   float sum, pic;
   int i;
   for(i=0;i<=n;i++)
   {
      scanf("%f",pic);
      sum=sum+fabs(pic-pIC[i]);
   }
   return sum/n;
}

float factor(int n)
{
   float h;
   if(n>=50)
       h=1;
   else if(n>=40)
       h=0.95f;
   else if(n>=30)
       h=0.9f;
   else if(n>=20)
       h=0.85f;
   else if(n>=10)
       h=0.8f;
   else
       h=0.75f;
   return h;
}

float score(float mae, float h)
{
   float s;

   if(mae<=0.3f) s=100;
   else if(mae<=0.5f) s=80;
   else if(mae<=0.7f) s=60;
   else if(mae<=0.9f) s=40;
   else if(mae<=1.1f) s=20;
   else s=0;
   return s*h;
}
