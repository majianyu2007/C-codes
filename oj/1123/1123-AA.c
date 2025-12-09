#include <stdio.h>

int main(void) {
    int a[3][4];
    int *p = &a[0][0];
    int i, j, k, max_pos = 0;

    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; ++j)
            if (scanf("%d", p + i * 4 + j) != 1)
                return -1;

    int max = *p;
    for (k = 1; k < 12; ++k) {
        if (*(p + k) > max) {
            max = *(p + k);
            max_pos = k;
        }
    }

    printf("%d %d %d", max_pos / 4, max_pos % 4, max);
    return 0;
}