#include "LinkedList.h"

int main()
{
    int sect_count = 0;
    struct Node head;
    int data;

    // 0. 向数组中插删元素
    printf("%d. 向数组的第0个位置插入元素100，再删除第1个元素\n", sect_count++);
    int arr[8] = {1, 2, 3, 4, 5, 6, 7};
    printf("  原数组: ");
    PrintIntArr(arr, 7);
    putchar('\n');
    
    // 插入100到第0个位置
    for (int i = 7; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = 100;
    printf("  插入100到第0个位置: ");
    PrintIntArr(arr, 8);
    putchar('\n');
    
    // 删除第1个元素（即原来的1）
    for (int i = 1; i < 7; i++)
    {
        arr[i] = arr[i + 1];
    }
    printf("  删除第1个元素后: ");
    PrintIntArr(arr, 7);
    putchar('\n');
    putchar('\n');

    // 1. 测试头插入、头删除、遍历输出
    printf("%d. 用头插入建立长度为10的整型链表1:1:10，\n\t输出后用头删除清空并释放\n", sect_count++);
    InitLinkedList(&head);
    for (int i = 1; i <= 10; i++)
    {
        HeadInsert(&head, i * 10);
    }
    printf("  建立的链表: ");
    PrintLinkedList(&head);
    putchar('\n');
    printf("  头删除过程: ");
    while (HeadDelete(&head, &data))
    {
        printf("%d ", data);
    }
    printf("\n\n");

    // 2. 测试尾插入、尾删除、遍历输出
    printf("%d. 用尾插入建立长度为10的整型链表100:100:1000，\n\t输出后用尾删除清空释放\n", sect_count++);
    InitLinkedList(&head);
    for (int i = 1; i <= 10; i++)
    {
        TailInsert(&head, i * 100);
    }
    printf("  建立的链表: ");
    PrintLinkedList(&head);
    putchar('\n');
    printf("  尾删除过程: ");
    while (TailDelete(&head, &data))
    {
        printf("%d ", data);
    }
    printf("\n\n");

    return 0;
}
