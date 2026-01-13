#include <stdio.h>
#include <string.h>

#define MAX_LEN 10

int Judge(char *, int);
int ReadLine(char *s);

int ReadLine(char *s)
{
    int n = 0, ch = 0;
    while((ch = getchar()) != '\n' && ch != EOF && n < MAX_LEN - 1)
        s[n++] = ch;
    s[n]='\0';
    return n;
}

int main()
{
    char str[MAX_LEN];
    int n;

    while (ReadLine(str) > 0){
        scanf("%d", &n);   /* 星期 */
        getchar();
        printf("%d\n", Judge(str, n));
    }
    return 0;
}

int Judge(char *plate_num, int day)
{
    if (plate_num == NULL) return -1;
    if (day < 1 || day > 7) return -1;
    size_t len = strlen(plate_num);
    if (len < 5 || len > 6) return -1;
    for (int i = 0; i < len; i++)
    {
        if (!(('A' <= plate_num[i] && plate_num[i] <= 'Z') || ('0' <= plate_num[i] && plate_num[i] <= '9'))) return -1;
    }
    if (len == 6) return 0;
    int digit = -1;
    for (int i = len - 1; i >= 0; i--)
    {
        if('0' <= plate_num[i] && plate_num[i] <= '9')
        {
            digit = plate_num[i] - '0';
            break;
        }
    }
    if (digit == -1) return -1;
    switch(day){
    case 1: if (digit == 1 || digit == 6) return 1; break;
    case 2: if (digit == 2 || digit == 7) return 1; break;
    case 3: if (digit == 3 || digit == 8) return 1; break;
    case 4: if (digit == 4 || digit == 9) return 1; break;
    case 5: if (digit == 5 || digit == 0) return 1; break;
    case 6:case 7: return 0;
    }
    return 0;
}
