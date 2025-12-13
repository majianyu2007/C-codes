#include <stdio.h> // 系统头文件通常使用<>引用，搜索系统路径
#include "myfunc.h" // 自建头文件通常使用""引用，搜索当前和系统路径

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    for(int i = 1; i <= 5; i++)
    {
        PrintIntArr(arr, i);
    }
    return 0;
}
