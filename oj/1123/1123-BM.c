#include <stdio.h>

int Operator(int *a, int *b, int *c) {
    int original_a = *a;
    int original_b = *b;
    int original_c = *c;
    
    // Find the maximum of original values
    int max = original_a;
    if (original_b > max) max = original_b;
    if (original_c > max) max = original_c;
    
    // Modify the values
    *a = original_a + original_b;
    *b = original_b + original_c;
    *c = original_c + original_a;
    
    return max;
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    int max = Operator(&a, &b, &c);
    
    printf("%d %d %d %d\n", a, b, c, max);
    
    return 0;
}