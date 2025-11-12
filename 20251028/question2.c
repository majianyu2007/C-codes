#include <stdio.h>

int main(void)
{
    int a=10, b=3, c=0; //声明变量

    //Step1 输出原始值
    printf("Initial values: a=%d, b=%d, c=%d\n", a, b, c);

    //Step2 计算a / b并输出
    c = a / b; //执行除法运算，并将结果赋给 c
    printf("After a / b: c=%d, a=%d, b=%d\n", c, a, b);

    //Step3 计算a % b并输出
    c = a % b; //执行取余运算，并将结果赋给 c
    printf("After a %% b: c=%d, a=%d, b=%d\n", c, a, b);

    //Step4 a前置自增并输出
    //a自增，在输出a之前对a执行自增运算
    printf("After ++a: c=%d, a=%d, b=%d\n", c, ++a, b);

    //Step5 b后置自减并输出
    b--; //在输出b之前对b执行自减运算
    printf("After b--: c=%d, a=%d, b=%d\n", c, a, b--);

    //Step6 使c赋值为a后置自增与b前置自减的积并输出
    c = a++ * --b; //a自增，但不立即改变；b自减，立即改变
    printf("After c = a++ * --b: c=%d, a=%d, b=%d\n", c, a, b);

    //Step7 输出最终结果
    //在Step4-6中，自增自减操作均独立成行，没有对输出造成影响
    printf("Final values: a=%d, b=%d, c=%d\n", a, b, c);

    return 0;
}

