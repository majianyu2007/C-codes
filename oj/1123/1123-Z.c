#include <stdio.h>

int main() {
    int arr[10];
    int *p = arr;
    int *min, *max;
    int i;
    
    for (i = 0; i < 10; i++) {
        scanf("%d", p + i);
    }
    
    min = max = p;
    for (i = 1; i < 10; i++) {
        if (*(p + i) < *min) {
            min = p + i;
        }
        if (*(p + i) > *max) {
            max = p + i;
        }
    }
    
    int temp = *min;
    *min = *p;
    *p = temp;
    
    if (max == p) {
        max = min;
    }
    
    temp = *max;
    *max = *(p + 9);
    *(p + 9) = temp;
    
    for (i = 0; i < 10; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");
    
    return 0;
}