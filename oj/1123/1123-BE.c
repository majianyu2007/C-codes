#include <stdio.h>

int main() {
    int count = 0;
    int ch;
    
    while ((ch = getchar()) != EOF) {
        if (ch == '{') {
            count++;
        } else if (ch == '}') {
            if (count == 0) {
                printf("No(-1)\n");
                return 0;
            }
            count--;
        }
    }
    
    if (count == 0) {
        printf("Yes\n");
    } else {
        printf("No(%d)\n", count);
    }
    
    return 0;
}