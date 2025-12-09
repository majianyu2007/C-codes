#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        char expr[32];
        if (scanf("%s", expr) != 1) {
            break;
        }
        size_t len = strlen(expr);
        size_t pos = 0;
        char op = '+';
        while (pos < len && expr[pos] != '+' && expr[pos] != '-') {
            pos++;
        }
        if (pos == len) {
            continue;
        }
        op = expr[pos];

        char lhs[32], rhs[32];
        memcpy(lhs, expr, pos);
        lhs[pos] = '\0';
        strcpy(rhs, expr + pos + 1);

        unsigned long long a = strtoull(lhs, NULL, 16);
        unsigned long long b = strtoull(rhs, NULL, 16);
        unsigned long long res = (op == '+') ? (a + b) : (a - b);

        printf("%llo\n", res);
    }
    return 0;
}