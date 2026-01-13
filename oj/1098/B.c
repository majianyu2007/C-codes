#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 128

int CheckLuhn ( const char * cardId, int sum[2] );
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
    int s[2]={0}, r;
    char id[MAX_LEN];

    while (ReadLine(id) > 0) {
        r = CheckLuhn(id, s);
        printf("%s,R=%d\t%d\t%d\n", id, r, s[0], s[1]);
    }
    return 0;
}

int CheckLuhn(const char * cardId , int sum[2])
{
    int len = strlen(cardId);
    
    sum[0] = 0;
    sum[1] = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        int j = len - i;
        if (j % 2 == 0)
        {
            sum[1] += cardId[i] - '0';
            continue;
        }
        sum[0] += cardId[i] - '0';
    }
    if ((sum[0] + sum[1]) % 10 == 0) return 0;
    return 1;
}


