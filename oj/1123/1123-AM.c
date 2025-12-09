#include <stdio.h>

int factorial(int n) {
    if (n == 0) return 1;
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int sum(int (*f)(int), int start, int end)
{
    if (f == NULL)
        return 0;

    if (start > end) {
        int t = start;
        start = end;
        end = t;
    }

    int total = 0;
    for (int i = start; i <= end; i++) {
        total += f(i);
    }
    return total;
}


int main() {
    int result = sum(factorial, 1, 4);
    printf("The sum is: %d\n", result);
    return 0;
}