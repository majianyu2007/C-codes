#include <stdio.h>

int main() {
    int a, b;
    scanf("%d/%d", &a, &b);
    
    printf("0.");
    
    int remainder = a;
    for (int i = 0; i < 200; i++) {
        remainder *= 10;
        int digit = remainder / b;
        remainder = remainder % b;
        printf("%d", digit);
        
        if (remainder == 0) {
            break;
        }
    }
    
    printf("\n");
    
    return 0;
}