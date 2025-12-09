#include <stdio.h>
#include <string.h>

int main(void) {
    char zfsour[100], zfdest[100];
    char *pzfsour, *pzfdest;
    int m, n;

    if (!fgets(zfsour, sizeof(zfsour), stdin)) 
    {
    return 0;
    }
    size_t len = strlen(zfsour);
    if (len > 0 && zfsour[len-1] == '\n') 
    {
        zfsour[--len] = '\0';
    }
    if (scanf("%d %d", &m, &n) != 2) 
    {
    return 0;
    }
    if (m < 0) 
    {
    m = 0;
    }
    if (n < 0) 
    {
    n = 0;
    }
    if ((size_t)m > len) 
    {
    printf("\n");
    return 0;
    }

    pzfsour = zfsour + m;
    pzfdest = zfdest;

    while (n-- > 0 && *pzfsour) {
        *pzfdest++ = *pzfsour++;
    }
    *pzfdest = '\0';

    printf("%s\n", zfdest);
    return 0;
}