#include <stdio.h>

union DoubleChar
{
    double d;
    char str[8];
};

int main()
{
    // 任务：按字节查看double类型的存储
    double d = 11.23456;
    union DoubleChar dc;
    dc.d = d;
    for(int i = 0; i < 8; i++)
        printf("%02x ", dc.str[i]);
    putchar('\n');
    return 0;
}
