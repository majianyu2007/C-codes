#include <stdio.h>

int main(void)
{
    int i = 0;
    float f = 0.0f;
    double d = 0.0;
    char ch = 'A';

    printf("这是%s的数据类型作业: \n", "马建宇");
    printf("int: %zu byte\n", sizeof(i));
    printf("float: %zu byte\n", sizeof(f));
    printf("double: %zu byte\n", sizeof(d));
    printf("char: %zu byte\n", sizeof(ch));

    return 0;
}
