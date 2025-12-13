#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    if (scanf("%s", input) != 1) {
        printf("Invalid input\n");
        return 0;
    }
    
    int len = strlen(input);
    
    // Check if input is valid (1-7 digits, all digits, no leading zero for multi-digit)
    if (len == 0 || len > 7) {
        printf("Invalid input\n");
        return 0;
    }
    
    for (int i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid input\n");
            return 0;
        }
    }
    
    // Check for leading zero (except for single digit "0")
    if (len > 1 && input[0] == '0') {
        printf("Invalid input\n");
        return 0;
    }
    
    // Count occurrences of each digit
    int count[10] = {0};
    for (int i = 0; i < len; i++) {
        count[input[i] - '0']++;
    }
    
    // Find repeated digits
    int repeated[10];
    int repeatedCount = 0;
    for (int i = 0; i < 10; i++) {
        if (count[i] > 1) {
            repeated[repeatedCount++] = i;
        }
    }
    
    if (repeatedCount == 0) {
        printf("No repeated numbers.\n");
    } else {
        for (int i = 0; i < repeatedCount; i++) {
            if (i > 0) printf(" ");
            printf("%d", repeated[i]);
        }
        printf("\n");
    }
    
    return 0;
}