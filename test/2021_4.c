#include<stdio.h>
void Days(int month,int days)
{
    int result=0;
    int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i=0;i<month-1;i++)
    {
        result+=mon[i];
    }
    printf("%d\n",result+days);
}

int main (void)
{
    int a,b,c;
    while (scanf("%d/%d/%d",&a,&b,&c) == 3)
    {
        Days(b,c);
    }
    return 0;

}
