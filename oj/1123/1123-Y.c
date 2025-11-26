#include <stdio.h>

int main() {
    int arr[10];
    int *p1, *p2, temp;
    
    for (int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }
    
    p1 = arr;
    p2 = arr + 9;
    
    while (p1 < p2) {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
        p1++;
        p2--;
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}