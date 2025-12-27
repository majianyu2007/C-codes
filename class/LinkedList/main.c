#include "LinkedList.h"

int main()
{
    int sect_count = 0;

    // 0. 向数组中插删元素
    printf("%d. 向数组的第0个位置插入元素100，再删除第1个元素\n", 
            sect_count++);
    int arr[8] = {1, 2, 3, 4, 5, 6, 7};
    PrintIntArr(arr, 7);
    for(int i = 7; i > 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = 100;
    PrintIntArr(arr, 8);

    for(int i = 1; i < 7; i++)
        arr[i] = arr[i + 1];
    PrintIntArr(arr, 7);

    putchar('\n');

    // 1. 测试头插入、头删除、遍历输出
    printf("%d. 用头插入建立长度为10的整型链表1:1:10，\n\t输出后用头删除清空并释放\n", sect_count++);
    struct Node *LinkedList1 = (struct Node *)malloc(sizeof(struct Node));
    InitLinkedList(LinkedList1);
    for(int i = 10; i > 0; i--)
        HeadInsert(LinkedList1, i);
    PrintLinkedList(LinkedList1);
    int data;
    while(HeadDelete(LinkedList1, &data))
    {
        printf("删掉了: %d\n", data);
        PrintLinkedList(LinkedList1);
    }
    free(LinkedList1);

    putchar('\n');

    // 2. 测试尾插入、尾删除、遍历输出
    printf("%d. 用尾插入建立长度为10的整型链表100:100:1000，\n\t输出后用尾删除清空释放\n", sect_count++);
    struct Node *LinkedList2 = (struct Node *)malloc(sizeof(struct Node));
    InitLinkedList(LinkedList2);
    for(int i = 100; i <= 1000; i += 100)
        TailInsert(LinkedList2, i);
    PrintLinkedList(LinkedList2);
    while(TailDelete(LinkedList2, &data))
    {
        printf("删除了: %d\n", data);
    }
    free(LinkedList2);

    putchar('\n');

    return 0;
}
