#include <stdio.h>
#include <math.h>

int main(void) {
    double pi = 0.0, prev = 0.0;
    long long i = 0;
    int sign = 1;
    while (1) {
        pi += sign * (4.0 / (2.0 * i + 1.0));
        if (fabs(pi - prev) < 1e-6) break;
        prev = pi;
        sign = -sign;
        ++i;
    }
    printf("Iterations: %lld\nPI ≈ %.10f\n", i + 1, pi);
    return 0;
}