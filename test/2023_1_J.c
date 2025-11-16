#include<stdio.h>
#include<math.h>

double Hi(int a,int s)
{
    if (a==0)
        return 0;
    else
    {
        double p=(double)a/s;
        return -p*log2(p);
    }
}
int main (void)
{
    int i=0,j=0,k=0;
    char ch;

    while ((ch=getchar()!='\n'))
    {
        switch (ch)
        {
            case 'a':i++;
                     break;
            case 'b':j++;
                     break;
            case 'c':k++;
                     break;
            default:break;
        }
    }

    int  num=i+j+k;
    float result=Hi(i,num)+Hi(j,num)+Hi(k,num);
    printf("%.3f",result);
    return 0;


}
