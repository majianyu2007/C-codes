#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Date
{
    int year;
    int month;
    int day;
};

struct StuNode
{
    int ID; // 4
    char name[20]; // 24
    char gender[13]; // 37 -> 40
    int age; // 44
    char *note; // 52
    struct Date birthday; // 64
};

void PrintStuNode(struct StuNode);
void Swap(struct StuNode *, struct StuNode *);

int main()
{
    int sect_count = 0;

    // 0. 当前的潜在问题
    printf("%d. 当前的潜在问题\n", sect_count++);
//    int stuNum = 100;
//    int ID[stuNum];
//    char name[stuNum][20];
//    char gender[stuNum][13];
//    int age[stuNum];
//    char *note[stuNum];
    putchar('\n');

    // 1. 结构体类型声明
    printf("%d. 结构体类型声明\n", sect_count++);
    // 将上述数据类型组合成结构体类型
    putchar('\n');

    // 2. 结构体变量的声明
    printf("%d. 结构体变量的声明\n", sect_count++);
    // 建立两个结构体变量stu1和stu2，用大括号赋值
    struct Date birth1 = {2007, 1, 1};
    struct StuNode stu1 = {2025123456, "西门吹雪", "男", 18, NULL, birth1};
    struct StuNode stu2 = {2025654321, "甘十九妹", "女", 18, NULL, 
                            (struct Date){2008, 2, 29}};
    

    // 编写函数打印stu1和sut2
    PrintStuNode(stu1);
    PrintStuNode(stu2);
    putchar('\n');

    // 3. 结构体指针的基本使用
    printf("%d. 结构体指针的基本使用\n", sect_count++);
    // 建立结构体指针p1指向stu1，p2指向stu2
    struct StuNode *p1 = &stu1;
    struct StuNode *p2;
    p2 = &stu2;

    // 修改p1指向的姓名为东方不败并输出
    strcpy((*p1).name, "东方不败");
    strcpy(p1->gender, "不详");
    PrintStuNode(stu1);

    p1->note = (char *)malloc(20);
    strcpy(p1->note, "这是stu1");
    p2->note = (char *)malloc(20);
    strcpy(p2->note, "这是stu2");
    

    // 用指针将备注改为"这是stu1"和"这是stu2"
    putchar('\n');

    // 4. 用函数交换结构体
    printf("%d. 用函数交换结构体\n", sect_count++);
    PrintStuNode(stu1);
    PrintStuNode(stu2);

    // 建立stu3并将stu1的信息复制给stu3
    struct StuNode stu3;
    stu3 = stu1;
    PrintStuNode(stu3);

    // 将stu3的备注改为"这是stu3"，姓名改为令狐冲，性别改为男
    // 学号改为2025000001
    stu3.note = (char *)malloc(20);
    strcpy(stu3.note, "这是stu3");
    strcpy(stu3.name, "令狐冲");
    strcpy(stu3.gender, "男");
    stu3.ID = 2025000001;
    stu3.birthday.year = 2007;
    stu3.birthday.month = 7;
    stu3.birthday.day = 7;


    PrintStuNode(stu3);


    // 交换stu1和stu2并检查
    Swap(&stu1, &stu2);
    PrintStuNode(stu1); //甘十九妹
    PrintStuNode(stu2); //东方不败

    putchar('\n');

    // 5. 结构体嵌套与赋值
    printf("%d. 结构体嵌套与赋值\n", sect_count++);
    // 为StuNode增加生日信息

    // 重设stu3的生日

    putchar('\n');

    // 6. 结构体的大小
    printf("%d. 结构体的大小\n", sect_count++);
    // 6.1 研究Date
    printf("Date的各元素相加: %lu\n", sizeof(int) * 3);
    printf("Date所占的实际字节数: %lu\n", sizeof(struct Date));
    putchar('\n');

    // 6.2 研究StuNode
    printf("StuNode的个元素相加: %lu\n", 
            sizeof(int) * 2 + sizeof(char) * 33 + 
            sizeof(char *) + sizeof(struct Date));
    printf("StuNode所占的实际字节数: %lu\n", sizeof(struct StuNode));
    printf("char *所占字节数: %lu\n", sizeof(char *));
    putchar('\n');

    // 6.3 思考以下两个结构体各占多少字节
    struct {
        char ch;
        int i;
        double d;
    } A;
    struct {
        char ch;
        double d;
        int i;
    } B;
    printf("A占%lu字节，B占%lu字节\n", sizeof(A), sizeof(B));

    return 0;
}


void PrintStuNode(struct StuNode stu)
{
    printf("这是%s同学的信息:\n", stu.name);
    printf("姓名: %s\n", stu.name);
    printf("学号: %d\n", stu.ID);
    printf("性别: %s\n", stu.gender);
    printf("年龄: %d\n", stu.age);
    printf("生日: %d-%d-%d\n", 
            stu.birthday.year, stu.birthday.month, stu.birthday.day);
    if(stu.note != NULL)
        printf("备注: %s\n", stu.note);
    putchar('\n');
}

void Swap(struct StuNode *a, struct StuNode *b)
{
    struct StuNode tmp = *a;
    *a = *b;
    *b = tmp;
}


