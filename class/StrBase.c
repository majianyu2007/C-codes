#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadLine(char []); // 按行读取字符串
int Strlen(const char *); // 获取字符串的实际长度
int Strcpy(char *, const char *); // 将第二个字符串复制给第一个字符串
char *Strcat(const char *, const char *); // 将两个字符串拼接
int StrIsEqual(const char *, const char *); // 判断两个字符串是否相等

int main()
{
    int sect_count = 0;
    
    // 1. 字符串的基本用法
    printf("%d. 字符串的基本用法\n", ++sect_count);

    char str1[200] = "今天终于进入字符串了，\n\t1. 用\"\"括起来的是字符串\n\t2. 用''括起来的是字符\n\t3. 字符串以'\\0'结尾\n";
    printf("%s", str1);
    
    char str2[4] = {'a', 'b', 'c', '\0'};
    str2[0] = 'A';
    //str2 = "12\0";
    puts(str2);
    
    char *ps1 = (char *)malloc(3 * sizeof(char));
    scanf("%2s", ps1);
    printf("用%%s打印ps1: %s\n", ps1);
    printf("用puts打印字符串会自动换行: ");
    puts(ps1);
    printf("用%%c打印ps1: %c%c%d\n", ps1[0], ps1[1], ps1[2]);
    free(ps1);
    printf("\n");

    // 2. 字符串字面量（字符串常量）
    printf("%d. 字符串字面量（字符串常量）\n", ++sect_count);
    ps1 = "hello, world!\n";
    char ch = ps1[0];
    printf("运行了ch = ps1[0];之后ch的值为: ");
    putchar(ch);
    ps1 = "你好，世界！\n";
    printf("\n使ps1指向了另一个字符串常量后: ");
    puts(ps1);
    ch = "0123456789ABCDEF"[15];
    printf("\n运行了ch = \"0123456789ABCDE\"[15];之后ch的值为: ");
    putchar(ch);
    printf("\n\n");

    // 3. const char *
    printf("%d. const char *\n\n", ++sect_count);
    const char *ps2 = "i am const pointer\n";
    //ps2[0] = 'I';
    //ps1[0] = 'H';
    
    // 4. 字符串的常用操作
    printf("%d. 字符串的常用操作\n", ++sect_count);
    getchar(); // 清理缓冲区中的\n
    ReadLine(str1);
    puts(str1);
    fgets(str1, 5, stdin);
    puts(str1);

    printf("str1现在的长度是: %d\n", Strlen(str1));

    Strcpy(str1, "C语言好简单！");
    puts(str1);

    char *ps3 = Strcat(str1, "真的好简单！");
    puts(ps3);

    printf("ps1和ps3是否相等的判断为: %d\n", StrIsEqual(ps1, ps3));
    
    free(ps3);
    printf("\n");

    // 5. string.h中的函数
    printf("%d. string.h中的函数\n", ++sect_count);
    getchar(); // 清理缓冲区中的\n
    fgets(str1, 5, stdin);

    printf("str1现在的长度是: %d\n", (int)strlen(str1));

    strcpy(str1, "C语言好简单！");
    puts(str1);

    strcat(str1, "真的好简单！");
    puts(str1);

    printf("str1和ps1是否相等的判断为: %d\n", strcmp(str1, ps1));


    return 0;
}

void ReadLine(char str[])
{
    char ch;
    int i = 0;
    while((ch = getchar()) != '\n')
    {
        str[i++] = ch;
    }
    str[i] = '\0';
}

int Strlen(const char *str)
{
    int i = 0;
    while(str[i++] != '\0');
    return i - 1;
}

int Strcpy(char *str1, const char *str2)
{
    int l2 = Strlen(str2);
    if(Strlen(str1) < l2)
        return 0;
    
    for(int i = 0; i < l2; i++)
    {
        str1[i] = str2[i];
    }
    str1[l2 - 1] = '\0';
    return 1;
}

char *Strcat(const char *str1, const char *str2)
{
    int l1 = Strlen(str1);
    int l2 = Strlen(str2);
    int len = l1 + l2 + 1;
    char *result = (char *)malloc(len * sizeof(char));
    for(int i = 0; i < len; i++)
    {
        if(i < l1)
        {
            result[i] = str1[i];
        }
        else
        {
            result[i] = str2[i - l1];
        }
    }
    result[len - 1] = '\0';
    return result;
}


int StrIsEqual(const char *str1, const char *str2)
{
    int l1 = Strlen(str1);
    if(l1 != Strlen(str2))
        return 0;

    for(int i = 0; i < l1; i++)
    {
        if(str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}


