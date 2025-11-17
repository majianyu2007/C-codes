#include <stdio.h>
#include <ctype.h>

int main() {
    char str[1000];
    int upper = 0, lower = 0, digit = 0, other = 0;

    fgets(str, sizeof(str), stdin);

    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            upper++;
        } else if (islower(str[i])) {
            lower++;
        } else if (isdigit(str[i])) {
            digit++;
        } else if (str[i] != '\n') {
            other++;
        }
    }

    printf("%d %d %d %d\n", upper, lower, digit, other);

    return 0;
}

