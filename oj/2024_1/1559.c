#include <stdio.h>
#include <stdlib.h>

#define N 30
void total(int s[], int n, int m);
void output(int s[], int n);
void sort(int s[],int n);

int main()
{
    int score[N]={0};
    int nq,num; // 小题数量和人数

    scanf("%d%d", &num,&nq);
    total(score,num,nq);
    sort(score,num);
    output(score,num);
    return 0;
}

void output(int s[], int n)
{
    int i;
    for (i=0; i<n-1; i++)
        printf("%d ", s[i]);
    printf("%d\n",s[i]);
}

void total(int s[], int n, int m)
{
    int sum=0, temp=0;
    for (int i=0; i < n; i++)
    {
        for (int j=0; j < m; j++)
        {
            scanf("%d", &temp);
            sum += temp;
            temp = 0;
        }
        s[i] = sum;
        sum = 0;
    }

}

void sort(int s[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (s[j] > s[j + 1]) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

