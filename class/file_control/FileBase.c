#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct StuNode
{
    int ID;
    char name[20];
    char gender[13];
    int age;
};

void InputStuNodeArr(struct StuNode *, int); // 输入结构体数组信息
void PrintStuNode(struct StuNode); // 输出结构体信息
void PrintStuNodeArr(struct StuNode *, int); // 输出结构体数组信息

void PrintStuNodeArr2File(FILE *, struct StuNode *, int);
void LoadStuNodeArrFromFile(FILE *, struct StuNode *, int);

int main()
{
    int sect_count = 0;

    // 1. 输入输出重定向
    printf("%d.1 建立结构体数组并输入相关信息\n", ++sect_count);
    struct StuNode stuArr[3];
    InputStuNodeArr(stuArr, 3);
    PrintStuNodeArr(stuArr, 3);

    printf("%d.2 多次测试输入输出\n", sect_count);
    putchar('\n');

    // 2. 文件的写入练习
    printf("%d. 文件的写入练习\n", ++sect_count);
    // 用w打开文件data.txt
    FILE *fp;
    fp = fopen("data.txt", "w");

    // 将建立的结构体数组写入文件
    PrintStuNodeArr2File(fp, stuArr, 3);
    fclose(fp);
    //_exit(-1);

    // 3. 文件的读取练习
    printf("%d. 文件的读取练习\n", ++sect_count);
    // 用r打开文件data.txt
    fp = fopen("data.txt", "r");
    if(fp == NULL)
        exit(-1);

    // 读取内容并打印到屏幕上
    struct StuNode loadtxt[3];
    LoadStuNodeArrFromFile(fp, loadtxt, 3);
    PrintStuNodeArr(loadtxt, 3);

    fclose(fp);
    // 4. 二进制文件的读写练习
    printf("%d. 文件的读写练习-binary\n", ++sect_count);
    fp = fopen("data.bin", "wb");
    if(fp == NULL)
        exit(-1);
    int n = 3;
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(stuArr, sizeof(struct StuNode), n, fp);
    fclose(fp);
    
    fp = fopen("data.bin", "rb");
    if(fp == NULL)
        exit(-1);
    n = -1;
    struct StuNode loadbin[3];
    fread(&n, sizeof(int), 1, fp);
    fread(loadbin, sizeof(struct StuNode), n, fp);
    fclose(fp);

    PrintStuNodeArr(loadbin, n);


    return 0;
}


void PrintStuNode(struct StuNode stu)
{
    printf("这是%s同学的信息\n", stu.name);
    printf("姓名: %s\n", stu.name);
    printf("学号: %d\n", stu.ID);
    printf("性别: %s\n", stu.gender);
    printf("年龄: %d\n", stu.age);
    putchar('\n');
}

void PrintStuNodeArr(struct StuNode *stus, int n)
{
    printf("以下输出%d位同学的信息:\n", n);
    for(int i = 0; i < n; i++)
    {
        PrintStuNode(stus[i]);
    }
    putchar('\n');
}

void PrintStuNodeArr2File(FILE *fp, struct StuNode *stus, int n)
{
    fprintf(fp, "以下输出%d位同学的信息:\n", n);
    for(int i = 0; i < n; i++)
    {
        fprintf(fp, "这是%s同学的信息\n", stus[i].name);
        fprintf(fp, "姓名: %s\n", stus[i].name);
        fprintf(fp, "学号: %d\n", stus[i].ID);
        fprintf(fp, "性别: %s\n", stus[i].gender);
        fprintf(fp, "年龄: %d\n\n", stus[i].age);
    }
}


void InputStuNodeArr(struct StuNode *stus, int n)
{
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &stus[i].ID);
        scanf("%s", stus[i].name);
        scanf("%s", stus[i].gender);
        scanf("%d", &stus[i].age);
    }
}

void LoadStuNodeArrFromFile(FILE *fp, struct StuNode *stus, int n)
{
    char tmp[50];
    fscanf(fp, "%s", tmp);
    for(int i = 0; i < n; i++)
    {
        fscanf(fp, "%s", tmp);
        fscanf(fp, "%s%s", tmp, stus[i].name);
        fscanf(fp, "%s%d", tmp, &stus[i].ID);
        fscanf(fp, "%s%s", tmp, stus[i].gender);
        fscanf(fp, "%s%d", tmp, &stus[i].age);
    }
}













