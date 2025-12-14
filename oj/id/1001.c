#include <stdio.h>
#include <stdbool.h>  // 使用bool类型需包含此头文件

// 二分查找函数：arr为有序数组，n为数组长度，target为目标值
bool binarySearch(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        // 计算中间索引，避免left+right溢出
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return true;  // 找到目标值
        } else if (arr[mid] < target) {
            left = mid + 1;  // 目标值在右半部分
        } else {
            right = mid - 1; // 目标值在左半部分
        }
    }
    return false; // 未找到目标值
}

int main() {
    int n;
    // 读取序列长度
    scanf("%d", &n);
    int arr[10000]; // 题目规定n不超过10000，数组大小足够
    // 读取n个整数到数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int m;
    // 读取查询次数
    scanf("%d", &m);
    // 处理每个查询
    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        if (binarySearch(arr, n, k)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}
