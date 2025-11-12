#include <stdio.h>

int main(void) 
{
    char ch = 'X'; // 字符变量
    int arr[3] = {10, 20, 30}; // 整型数组，包含3个元素
    int num = 100; // 整型变量
    float f = 3.14f; // 浮点型变量
    
    // 打印各变量的地址和值
    printf("Address of ch: %p, Value: %c\n", &ch, ch);
    printf("Address of arr: %p, arr[0]: %d\n", &arr[0], arr[0]);
    printf("Address of arr[1]: %p, Value: %d\n", &arr[1], arr[1]);
    printf("Address of arr[2]: %p, Value: %d\n", &arr[2], arr[2]);
    printf("Address of num: %p, Value: %d\n", &num, num);
    printf("Address of f: %p, Value: %f\n", &f, f);
    
    return 0;
}
