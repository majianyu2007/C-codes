#include "LinkedList.h"

int main()
{
    int sect_count = 0;

    // 0. 向数组中插删元素
    printf("%d. 向数组的第0个位置插入元素100，再删除第1个元素\n", sect_count++);
    int arr[8] = {1, 2, 3, 4, 5, 6, 7};
    PrintIntArr(arr, 7);
    putchar('\n');

//    // 1. 测试头插入、头删除、遍历输出
//    printf("%d. 用头插入建立长度为10的整型链表1:1:10，\n\t输出后用头删除清空并释放\n", sect_count++);
//    putchar('\n');

//    // 2. 测试尾插入、尾删除、遍历输出
//    printf("%d. 用尾插入建立长度为10的整型链表100:100:1000，\n\t输出后用尾删除清空释放\n", sect_count++);
//    putchar('\n');

    return 0;
}
