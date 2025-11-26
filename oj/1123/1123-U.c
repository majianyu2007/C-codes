#include <stdio.h>
#include <string.h>

#define N 10
#define MAXLEN 100

int main(void) {
    char names[N][MAXLEN];
    for (int i = 0; i < N; i++) {
        if (scanf("%99s", names[i]) != 1) return 0;
    }

    for (int i = 0; i < N - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < N; j++) {
            if (strcmp(names[j], names[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            char tmp[MAXLEN];
            strcpy(tmp, names[i]);
            strcpy(names[i], names[min_index]);
            strcpy(names[min_index], tmp);
        }
    }

    for (int i = 0; i < N; i++) {
        puts(names[i]);
    }
    return 0;
}