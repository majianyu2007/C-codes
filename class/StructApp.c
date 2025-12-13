#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StuNode
{
    int ID;
    char name[20];
};

void Swap(struct StuNode *, struct StuNode *);
void PrintStuNode(struct StuNode);
void PrintStuNodeArr(struct StuNode *, int);
int Comp(const void *, const void *);

// 以下两个函数是课下补完的
void SelectionSort(struct StuNode *, int);
void InsertSort(struct StuNode *, int);

int main()
{
    int sect_count = 0;

    // 1. 普通(静态)结构体变量和动态结构体变量
    printf("%d. 动态结构体变量\n", ++sect_count);
    struct StuNode stu = {0, "尼克"};
    // 创建一个动态结构体变量
    struct StuNode *ps = (struct StuNode *)malloc(1 * sizeof(struct StuNode));

    // 将ps的信息置为"朱迪"，ID=1
    ps->ID = 1;
    strcpy(ps->name, "朱迪");
    
    // 打印并查看信息
    PrintStuNode(stu);
    PrintStuNode(*ps);

    putchar('\n');

    // 2. 结构体数组
    printf("%d. 结构体数组\n", ++sect_count);
    int n = 10;
    // 创建长度为 n 的结构体数组 students并以大括号的方法初始化
    struct StuNode students1[] = {{2, "9葫芦爷爷"}, 
                                  {3, "8大娃"},
                                  {4, "7二娃"},
                                  {5, "6三娃"},
                                  {6, "5四娃"},
                                  {7, "4五娃"},
                                  {8, "3六娃"},
                                  {9, "2七娃"},
                                  {10, "1蛇精"},
                                  {11, "0黑猫警长"}
                                 };
    struct StuNode students2[] = {(struct StuNode){2, "0葫芦爷爷"}, 
                                  (struct StuNode){3, "1大娃"},
                                  (struct StuNode){4, "2二娃"},
                                  (struct StuNode){5, "3三娃"},
                                  (struct StuNode){6, "4四娃"},
                                  (struct StuNode){7, "5五娃"},
                                  (struct StuNode){8, "6六娃"},
                                  (struct StuNode){9, "7七娃"},
                                  (struct StuNode){10, "8蛇精"},
                                  (struct StuNode){11, "9黑猫警长"}
                                 };

    // 创建长度为 n 的动态结构体数组 ds1 并将 students1 的数据复制过来
    struct StuNode *ds1 = (struct StuNode *)malloc(n * sizeof(struct StuNode));
    for(int i = 0; i < n; i++)
    {
        ds1[i] = students1[i];
    }
    
    strcpy(students1[9].name, "9蛤蟆精");
    strcpy(students2[9].name, "9蛤蟆精");
    strcpy(ds1[9].name, "9蛤蟆精");

    // 打印 ds1
    PrintStuNodeArr(ds1, n);

    putchar('\n');

    // 3. 结构体排序
    printf("%d. 结构体排序\n", ++sect_count);
    // 用选择排序使students1以学号升序排序
    puts("对students1以学号升序排序");
    SelectionSort(students1, n);
    PrintStuNodeArr(students1, n);

    // 用插入排序使students2以姓名升序排序
    puts("对students2以姓名升序排序");
    InsertSort(students2, n);
    PrintStuNodeArr(students2, n);

    // 用快速排序使ds1以姓名升序排序
    puts("对ds1以姓名升序排序");
    qsort(ds1, n, sizeof(ds1[0]), Comp);
    PrintStuNodeArr(ds1, n);

    putchar('\n');

    // 4. 是不是忘了点事情？
    free(ds1);
    free(ps);

    return 0;
}

void Swap(struct StuNode *stu1, struct StuNode *stu2)
{
    struct StuNode tmp = *stu1;
    *stu1 = *stu2;
    *stu2 = tmp;
}

void PrintStuNode(struct StuNode stu)
{
    printf("这是%s同学的信息：\n", stu.name);
    printf("学号: %d\n", stu.ID);
    printf("姓名: %s\n", stu.name);
    putchar('\n');
}

void PrintStuNodeArr(struct StuNode *stus, int n)
{
    for(int i = 0; i < n; i++)
    {
        PrintStuNode(stus[i]);
    }
}

int Comp(const void *p1, const void *p2)
{
    char *a = (*(struct StuNode *)p1).name;
    char *b = (*(struct StuNode *)p2).name;
    return strcmp(a, b);
}

void SelectionSort(struct StuNode *stus, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int minInd = i;
        for(int j = i + 1; j < n; j++)
        {
            if(stus[j].ID < stus[minInd].ID)
            {
                minInd = j;
            }
        }
        if(minInd != i)
        {
            Swap(&stus[minInd], &stus[i]);
        }
    }
}

void InsertSort(struct StuNode *stus, int n)
{
    for(int i = 1; i < n; i++)
    {
        int j = i - 1;
        struct StuNode tmp = stus[i];
        while(j >= 0 && Comp(&stus[j], &tmp) > 0)
        {
            stus[j + 1] = stus[j];
            j--;
        }
        stus[j + 1] = tmp;
    }
}

