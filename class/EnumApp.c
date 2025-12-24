#include <stdio.h>

#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESSDAY 3
#define THRSDAY 4
#define FRIDAY 5
#define SATURDAY 6

#define TRUE 1
#define FALSE 0

enum BOOL {False, True};

int Larger(int a, int b)
{
    if(a > b)
        //return TRUE;
        return True;
    else
        //return FALSE;
        return False;
}

int main()
{
    printf("星期天是: %d\n", SUNDAY);
    // 1. 用枚举实现以上内容
    enum week {MON = 1, TUE, WED, THR, FRI, SAT, SUN};
    printf("星期天是: %d\n", SUN);
    printf("今天是: %d\n", MON);


    // 2. 用枚举构建BOOL类型
    printf("3比5大的判断是：%d\n", Larger(3, 5));

    return 0;
}
