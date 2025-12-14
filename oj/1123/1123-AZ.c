#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    if (scanf("%s", input) != 1) {
        printf("Invalid input\n");
        return 0;
    }
    
    if (input[0] == '0') {
        printf("Invalid input\n");
        return 0;
    }

    int len = strlen(input);

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
    
    if (len > 1 && input[0] == '0') {
        printf("Invalid input\n");
        return 0;
    }
    
    int count[10] = {0};
    for (int i = 0; i < len; i++) {
        count[input[i] - '0']++;
    }
    
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
