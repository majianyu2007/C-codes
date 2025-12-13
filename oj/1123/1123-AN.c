#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
    int Data; /* 存储结点数据 */
    PtrToNode Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

// 计算阶乘的辅助函数
int Factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 求单向链表L中所有结点的Data域的阶乘和
int FactorialSum(List L) {
    int sum = 0;
    PtrToNode current = L;
    
    while (current != NULL) {
        sum += Factorial(current->Data);
        current = current->Next;
    }
    
    return sum;
}

// 测试代码
int main() {
    // 创建测试链表: 3 -> 4 -> 2
    List head = (List)malloc(sizeof(struct Node));
    head->Data = 3;
    head->Next = (PtrToNode)malloc(sizeof(struct Node));
    head->Next->Data = 4;
    head->Next->Next = (PtrToNode)malloc(sizeof(struct Node));
    head->Next->Next->Data = 2;
    head->Next->Next->Next = NULL;
    
    // 3! + 4! + 2! = 6 + 24 + 2 = 32
    printf("阶乘和: %d\n", FactorialSum(head));
    
    // 释放内存
    PtrToNode temp;
    while (head != NULL) {
        temp = head;
        head = head->Next;
        free(temp);
    }
    
    return 0;
}