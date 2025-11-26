#include <stdio.h>
#include <string.h>

#define N 10
#define MAX_LEN 20

int main() {
    char str[N][MAX_LEN];
    char *p[N];
    char *temp;
    int i, j;
    
    for (i = 0; i < N; i++) {
        p[i] = str[i];
    }
    
    for (i = 0; i < N; i++) {
        scanf("%s", p[i]);
    }
    
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - 1 - i; j++) {
            if (strcmp(p[j], p[j + 1]) > 0) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    for (i = 0; i < N; i++) {
        printf("%s\n", p[i]);
    }
    
    return 0;
}