#include <stdio.h>
#include <string.h>

#define N 10
#define MAXLEN 128

void sort_algorithm(char *str[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(str[j], str[j + 1]) > 0) {
                char *tmp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = tmp;
            }
        }
    }
}

void output_array(char *str[], int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%s, ", str[i]);
    }
    printf("%s\n", str[n - 1]);
}

static void strip_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void) {
    char buf[N][MAXLEN + 1];
    char *p[N];

    for (int i = 0; i < N; i++) {
        if (fgets(buf[i], sizeof(buf[i]), stdin) == NULL) {
            buf[i][0] = '\0';
        }
        strip_newline(buf[i]);
        p[i] = buf[i];
    }

    sort_algorithm(p, N);
    output_array(p, N);

    return 0;
}
