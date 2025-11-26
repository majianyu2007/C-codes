#include <stdio.h>

void sort(int *arr, int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

int main() {
    int arr[10];
    int *p = arr;
    int i;
    
    for (i = 0; i < 10; i++) {
        scanf("%d", p + i);
    }
    
    sort(arr, 10);
    
    for (i = 0; i < 10; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");
    
    return 0;
}