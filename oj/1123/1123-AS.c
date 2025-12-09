#include <stdio.h>
#include <string.h>

int main() {
    int m;
    char liked[1001];
    char classmates[1001];
    
    scanf("%d", &m);
    scanf("%s", liked);
    scanf("%s", classmates);
    
    int liked_set[26] = {0};
    for (int i = 0; liked[i]; i++) {
        liked_set[liked[i] - 'A'] = 1;
    }
    
    int found = 0;
    int first = 1;
    
    for (int i = 0; classmates[i]; i++) {
        int id = i + 1;
        
        if (id == m) continue;
        
        if (liked_set[classmates[i] - 'A']) {
            if (!first) printf(" ");
            printf("%d", id);
            first = 0;
            found = 1;
        }
    }
    
    if (!found) {
        printf("Lonely Xiao Ming\n");
    } else {
        printf("\n");
    }
    
    return 0;
}