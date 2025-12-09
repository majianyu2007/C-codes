#include <stdio.h>
#include <ctype.h>

int count(const char *s) {
    int cnt = 0;
    while (*s) {
        if (isdigit((unsigned char)*s)) 
        {
            cnt++;
        }
        s++;
    }
    return cnt;
}

int main(void) {
    char buf[1024];
    if (fgets(buf, sizeof(buf), stdin) != NULL) 
    {
        printf("%d\n", count(buf));
    }
    return 0;
}