#include <stdio.h>

int main(void)
{
    int a, b;
    if ((scanf("%d/%d", &a, &b)) != 2) return 1;
    if (!(a >= 10 && a < b && b < 100)) return 1;
    int m = a, n = 0;
    printf("0.");
    int counter = 1 ;
    do {
        printf("%d", m * 10 / b);
        n = m * 10 % b;
        m = n;
        counter++;
    } while (m != 0 && counter <= 200);

    printf("\n");

    return 0;
}
