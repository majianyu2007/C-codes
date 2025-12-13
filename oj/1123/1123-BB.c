#include <stdio.h>

int main() {
    char ch;
    scanf("%c", &ch);
    
    for (int i = 7; i >= 0; i--) {
        printf("%d", (ch >> i) & 1);
    }
    printf("\n");
    
    return 0;
}