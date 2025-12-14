#include <stdio.h>

void Swap(int *pa, int *pb) {
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void BubbleSort(int a[], int n) {
    int i, j;
    i = 0;
    while (i < n - 1) {
        j = 0;
        while (j < n - 1 - i) {
            if (a[j] > a[j + 1]) {
                Swap(&a[j], &a[j + 1]);
            }
            j++;
        }
        i++;
    }
}

void ResetArray(int input[], int n, int output[]) {
    int k, a;
    k = 1;
    a = 1;
    
    BubbleSort(input, n);
    
    output[n / 2] = input[0];
    
    while (k < n) {
        output[n / 2 - a] = input[k++];
        a++;
        output[n / 2 + a - 1] = input[k++];
    }
}

int main() {
    int input[100], output[100];
    int n, i;
    
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &input[i]);
    }
    
    ResetArray(input, n, output);
    
    for (i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", output[i]);
    }
    printf("\n");
    
    return 0;
}
