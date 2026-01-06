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

