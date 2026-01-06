#include <stdio.h>
#include <stdlib.h>

#define M 30

typedef struct STUDENT
{
    int studentID;
    char studentName[10];
    float score[3];
} stu, *pstu;
typedef int (*CmpFunPtr)(float, float);  /* 定义一个函数指针类型CallBack，该类型的指针对应的函数,要求返回值是一个整型数据，且含有两个浮点型形参。 */

int compareA(float, float);    /* 降序排列比较函数 */
int compareD(float, float);    /* 升序排列比较函数 */
stu *read( FILE *fp, int m, int n);
void sort(stu *stud, int mode, int sub, int n);
void print(pstu stud, int n);
CmpFunPtr setmode(int mode);        /* 返回一个CallBack类型的函数指针 */

int main()
{
    struct STUDENT *stud;
    
    FILE *fp;
    int m,n,mode,sub;
    scanf("%d%d%d%d",&m,&n,&mode,&sub);
    if(m < 0 || m > M || n < 0 || n + m > M || (mode != 1 && mode != 2) || (sub != 0 && sub != 1 && sub != 2))
    {
        printf("error!\n");
        exit(0);
    }
    fp = fopen("stud.dic", "rb");
    if(fp == NULL )
        exit(0);
    stud = read(fp, m, n);
    sort(stud, mode, sub, n);
    print(stud, n);
    free(stud);
    fclose(fp);
    return 0;
}
CmpFunPtr setmode(int mode)
{
    if (mode == 1)
        return compareD;
    else
        return compareA;
}
void print(pstu stud, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%dth: %d %s %.2f %.2f %.2f\n",i,stud[i].studentID,stud[i].studentName,stud[i].score[0],stud[i].score[1],stud[i].score[2]);
    }
}

int compareA(float x, float y)
{
    return x > y;
}
int compareD(float x, float y)
{
    return x < y;
}

