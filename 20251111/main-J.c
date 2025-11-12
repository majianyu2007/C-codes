#include<stdio.h>
char Int2Char(int);
int Power(int ,int);
int Base2Dec(int ,char *);
void Dec2Base(int , int, char*);
void Reverse(char*);
void Base2Base(int base_from, int base_to, char*num_from, char*num_to);
int Strlen(char *);
int Char2Int(char ch);


int main(void)
{
    int base_from, base_to;
    char num_from[11];
    char num_to[11];

    scanf("%d %s %d", &base_from, num_from, &base_to);
    Base2Base(base_from, base_to, num_from, num_to);
    printf("%s\n", num_to);
    return 0;

}
char Int2Char(int d)
{

    if (d>=0&&d<=9)
    {
        return d+'0';
    }
    switch(d)
    {
        case 10:return 'A';
                break;
        case 11:return 'B';
                break;
        case 12:return 'C';
                break;
        case 13:return 'D';
                break;
        case 14:return 'E';
                break;
        case 15:return 'F';
                break;
        default:return 'f';
                break;
    }
}
int Power(int base ,int exp)
{

    int m=1;
    for (int i=0;i<exp;i++)
    {
        m*=base;
    }
    return m;
}
int Strlen(char *str)
{
    int i=0;
    while (str[i]!='\0')
        i++;
    return i;
}

int Base2Dec(int base,char *num)
{
    int value=0;
    int cal;
    int len=Strlen(num);
    for(int j=0;j<len;j++)
    {
        cal=Char2Int(num[j]);
        value=cal*Power(base,len-j-1)+value;
    }
    return value;
}

void Dec2Base(int num , int base, char*converted)
{
    int i=0;
    if (num==0)
    {
        converted[0]='0';
        converted[1]='\0';
        return;
    }
    while(num>0)
    {

        converted[i]=Int2Char(num%base);
        num= num / base;
        i++;
    }
    converted[i]='\0';


}

void Reverse(char*str)
{
    int len=Strlen(str);

    for (int i=0;i<len/2;i++)
    {
        char temp=str[i];
        str[i]=str[len-1-i];
        str[len-1-i]=temp;
    }

}

void Base2Base(int base_from, int base_to, char*num_from, char*num_to)
{
    int value=Base2Dec(base_from,num_from);

    Dec2Base(value,base_to,num_to);
    Reverse(num_to);
}

int Char2Int(char ch)
{
    if (ch>='0'&&ch<='9')
        return ch-'0';
    switch (ch)
    {
        case'A': return 10;
                 break;
        case'B': return 11;
                 break;
        case'C': return 12;
                 break;
        case'D': return 13;
                 break;
        case'E': return 14;
                 break;
        case'F': return 15;
                 break;
        default:return-1;
                break;
    }
}
