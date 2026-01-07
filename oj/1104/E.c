#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct solu
{
    int x;
    int y;
    char direction;
};

int Judge(char **, int,  char, struct solu *);

int main()
{
    int n;
    char ch;
    struct solu s = {-1, -1, ' '};
    scanf("%c%d", &ch, &n);

    char *board[n];
    for(int i = 0; i < n; i++)
    {
        board[i] = (char *)malloc((n+1)*sizeof(char));
        memset(board[i], 0, (n+1)*sizeof(char));
        scanf("%s", board[i]);
    }

    if (Judge(board, n, ch, &s) == 1)
        printf("%d %d %c\n", s.x, s.y, s.direction);
    else
        printf("0\n");

    for(int i = 0; i < n; i++)
    {
        free(board[i]);
    }
    return 0;
}

int Judge(char **str, int n, char ch, struct solu *ps)
{
    char t = '\0';
    int i = 0;
    int j = 0;
aaa:
    if(i < n)
    {
        j = 0;
bbb:
        if(j < n)
        {
            if(str[i][j] == ch)
            {
                if(j <= n-5 && str[i][j+1] == ch && str[i][j+2] == ch && str[i][j+3] ==ch && str[i][j+4] == ch)
                {
                    t = '-';
                    goto ccc;
                }
                else
                {
                    if(i <= n-5 && str[i+1][j] == ch && str[i+2][j] == ch && str[i+3][j] ==ch && str[i+4][j] == ch)
                    {
                        t = '|';
                        goto ccc;
                    }
                    else
                    {
                        if(i <= n-5 && j <= n-5 && str[i+1][j+1] == ch && str[i+2][j+2] == ch && str[i+3][j+3] ==ch && str[i+4][j+4] == ch)
                        {
                            t = '\\';
                            goto ccc;
                        }
                        else
                        {
                            if(j >= 4 && i <= n-5 && str[i+1][j-1] == ch && str[i+2][j-2] == ch && str[i+3][j-3] ==ch && str[i+4][j-4] == ch)
                            {
                                t = '/';
                                goto ccc;
                            }
                            else
                            {
                                goto ccc;
                            }
                        }
                    }
                }
            }
            else
            {
                j++;
                goto bbb;
            }

        }
        else
        {
            i++;
            goto aaa;
        }
    }
    else
    {
        return 0;
    }

ccc:
    if(t != '\0')
    {
        ps->x = i;
        ps->y = j;
        ps->direction = t;
        return 1;
    }
    else
    {
        j++;
        goto bbb;
    }

}
