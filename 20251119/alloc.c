#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = NULL;
    int capacity = 5;
    int size = 0;

    arr = (int*)malloc(capacity * sizeof(int));

    while (1) {
        int x;
        printf("输入一个数字（-1结束）：");
        scanf("%d", &x);

        if (x == -1) break;

        if (size == capacity) {
            // 扩容
            int *tmp = (int*)realloc(arr, (capacity * 2) * sizeof(int));
            if (!tmp) {
                printf("扩容失败\n");
                free(arr);
                return 1;
            }
            arr = tmp;
            capacity *= 2;
        }

        arr[size++] = x;
    }

    printf("你输入的数字：");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}
