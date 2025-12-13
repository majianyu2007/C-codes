#include <stdio.h>

int main() {
    double result, num;
    char op;
    
    // Read the first number
    if (scanf("%lf", &result) == EOF) {
        return 0;
    }
    
    // Read operator and number pairs until EOF
    while (scanf("%c%lf", &op, &num) != EOF) {
        switch (op) {
            case '+':
                result += num;
                break;
            case '-':
                result -= num;
                break;
            case '*':
                result *= num;
                break;
            case '/':
                result /= num;
                break;
        }
    }
    
    printf("%.3f\n", result);
    
    return 0;
}