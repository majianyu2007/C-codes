#include <stdio.h>

int main(void)
{
    int a, b, c, t;

    scanf("%d%*c%d%*c%d",&a, &b, &c);

    printf("排序前：%d, %d, %d\n", a, b, c);

    if ( a > b ){
        a = a;
        b = b;
    }else{
        t = a;
        a = b;
        b = t;
    }
    if ( a > c ){
        a = a;
        c = c;
    }else{
        t = a;
        a = c;
        c = t;
    }
    if ( b > c ){
        b = b;
        c = c;
    }else{
        t = b;
        b = c;
        c = t;
    }
    printf("排序后：%d, %d, %d\n", a, b, c);
    return 0;
}
