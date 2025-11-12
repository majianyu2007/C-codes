#include <stdio.h>

int main(void)
{
    int x = 1;
    do {x++;} while (!( (x - 1) % 2 == 0 && (x - 2) % 3 == 0 && (x - 4) % 5 == 0 && (x - 5) % 6 == 0 && x % 7 == 0 ));
    printf("%d\n", x);
    return 0;
}

