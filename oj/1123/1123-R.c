#include <stdio.h>

int main(void) {
    int a[5][5];
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            scanf("%d", &a[i][j]);

    int main_sum = 0, secondary_sum = 0;
    for (int i = 0; i < 5; ++i) {
        main_sum += a[i][i];
        secondary_sum += a[i][4 - i];
    }

    printf("%d %d\n", main_sum, secondary_sum);
    return 0;
}