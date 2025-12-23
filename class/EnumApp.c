#include <stdio.h>

#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESSDAY 3
#define THRSDAY 4
#define FRIDAY 5
#define SATURDAY 6

// 1. 用枚举实现星期
enum Weekday {
    SUN = 0,    // 显式指定从0开始
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5,
    SAT = 6
};

// 也可以这样写，默认从0开始自动递增
enum Day {
    SUNDAY_E,   // 0
    MONDAY_E,   // 1
    TUESDAY_E,  // 2
    WEDNESDAY_E,// 3
    THURSDAY_E, // 4
    FRIDAY_E,   // 5
    SATURDAY_E  // 6
};

// 2. 用枚举构建BOOL类型
enum Bool {
    FALSE = 0,
    TRUE = 1
};

// 也可以用typedef定义类型别名，使用更方便
typedef enum {
    False = 0,
    True = 1
} BOOL;

int main()
{
    // 使用枚举变量
    enum Weekday today = WED;
    printf("今天是星期: %d\n", today);
    
    // 使用枚举判断
    if (today == WED) {
        printf("今天是星期三\n");
    }
    
    // 使用BOOL类型
    BOOL isWeekend = False;
    enum Weekday checkDay = SAT;
    
    if (checkDay == SAT || checkDay == SUN) {
        isWeekend = True;
    }
    
    if (isWeekend) {
        printf("周末啦！\n");
    } else {
        printf("工作日\n");
    }
    
    // 枚举在switch中的应用
    enum Day currentDay = FRIDAY_E;
    switch (currentDay) {
        case MONDAY_E:
            printf("周一，新的一周开始\n");
            break;
        case FRIDAY_E:
            printf("周五，快到周末了\n");
            break;
        case SATURDAY_E:
        case SUNDAY_E:
            printf("周末，休息日\n");
            break;
        default:
            printf("工作日\n");
    }
    
    // 打印枚举的值
    printf("\n枚举值演示：\n");
    printf("SUN = %d\n", SUN);
    printf("MON = %d\n", MON);
    printf("FALSE = %d\n", FALSE);
    printf("TRUE = %d\n", TRUE);

    return 0;
}
