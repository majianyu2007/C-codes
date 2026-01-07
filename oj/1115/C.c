#include <stdio.h>

char Encryption(char ch, int k);  // 声明你写的函数

int main() {
    char ch;
    int k;

    // 输入一个字符和偏移量
    printf("请输入一个字符和偏移量：");
    scanf(" %c %d", &ch, &k);

    // 调用加密函数
    char result = Encryption(ch, k);

    // 输出结果
    printf("加密后结果：%c\n", result);

    return 0;
}

char Encryption(char ch, int k)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return (ch - 'a' + k) % 26 + 'a';
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        return (ch - 'A' + k) % 26 + 'A';
    }
    else
    {
        return ch;
    }
}

