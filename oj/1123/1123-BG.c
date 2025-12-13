#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int judge(int a[], int n, int *cd) {
    if (n < 3) {
        return -1;
    }
    
    // Sort the array to check if it can form an increasing arithmetic sequence
    qsort(a, n, sizeof(int), compare);
    
    // Calculate the common difference
    *cd = a[1] - a[0];
    
    // Check if all consecutive differences are equal
    for (int i = 2; i < n; i++) {
        if (a[i] - a[i - 1] != *cd) {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int cd;
    int result = judge(a, n, &cd);
    
    if (result == -1) {
        printf("-1\n");
    } else if (result == 1) {
        printf("1\n");
    } else {
        printf("0\n");
        printf("%d\n", cd);
    }
    
    return 0;
}