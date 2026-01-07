#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int year;
    unsigned int month;
    unsigned int day;
} Date, *PDate;

int ToDate(char *, PDate);
int DaysCount(PDate, PDate);
int is_leap(int);
int month_days(int ,int);

int main()
{
    char str1[12], str2[12];
    Date sd, ed;
    fgets(str1, 12, stdin);
    fgets(str2, 12, stdin);
    if (ToDate(str1, &sd) == 0 && ToDate(str2, &ed) == 0)
        printf("%d\n", DaysCount(&sd, &ed));
    else
        printf("input data is invalid.\n");
    return 0;
}

int is_leap(int year)
{
    return ((year%4==0&&year%100!=0)||year%400==0);
}

int month_days(int month, int leap)
{
    int m_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(month == 2)
        return (leap == 1) ? 29 : 28;
    else
        return m_days[month];
}
/* 以上代码禁止提交 */

int ToDate(char *str, PDate pd)
{
    int year, month, day;
    if (sscanf(str, "%d-%d-%d", &year, &month, &day) != 3)
        return -1;
    
    if (year < 1900 || year > 2050)
        return -1;
    
    if (month < 1 || month > 12)
        return -1;
    
    if (day < 1 || day > month_days(month, is_leap(year)))
        return -1;
    
    pd->year = year;
    pd->month = month;
    pd->day = day;
    
    return 0;
}
int DaysCount(PDate sdate, PDate edate)
{
    int count = 0;
    unsigned int y1=sdate->year, m1=sdate->month, d1=sdate->day;
    unsigned int y2=edate->year, m2=edate->month, d2=edate->day;
    
    while(y1 != y2)
    {
        count += month_days(m1, is_leap(y1)) - d1 + 1;
        m1++;
        d1 = 1;
        for(int i = m1; i <= 12; i++)
        {
            count += month_days(i, is_leap(y1));
        }
        y1++;
        m1 = 1;
    }

    while(m1 != m2)
    {
        count += month_days(m1, is_leap(y1)) - d1 + 1;
        d1 = 1;
        if(++m1 == m2) break;
        for(int i = m1; i < m2; i++)
        {
            count += month_days(i, is_leap(y1));
        }
        m1 = m2;
    }

    while(d1 != d2)
    {
        count += d2 - d1;
        d1 = d2;
    }

    return count;
}

