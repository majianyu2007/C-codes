#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "multi_files/myfunc.h"

void PrintChar2D(const char *, int, int); // 完整打印二维字符型数组
void CharA2IntA(int *, const char *, int, int); // 二维字符型数组转为，参数应包括各维长度
void Char2DCpy(char *, const char *, int, int); // 复制二维字符数组
int Comp(const void *, const void *); // 利用qsort进行排序的预备工作
char *CombineStrs(const char *, int, int); // 合并字符串
void SepStrs(char *, char); // 按分隔符拆分字符串 


int main() {
    int sect_count = 0;

    // 1. 二维字符型数组转整型数组
    printf("%d. 二维字符型数组转整型数组\n", ++sect_count);
    char NumStr[5][5] = {"42", "0", "123", "999", "7"};
    // 完整打印该二维字符型数组
    PrintChar2D((char *)NumStr, 5, 5);

    int Nums[5];
    // 将NumStr转换为整型的Nums
    CharA2IntA(Nums, (char *)NumStr, 5, 5);

    PrintIntArr(Nums, 5);
    puts("");

    // 2. 将NumStr的内容备份
    printf("%d. 将NumStr的内容备份\n", ++sect_count);
    char Backup[5][5];
    // 利用Backup备份NumStr
    Char2DCpy((char *)Backup, (char *)NumStr, 5, 5);
    // 完整打印Backup
    PrintChar2D((char *)Backup, 5, 5);

    // 3. 将NumStr排序并输出（不是用已转好的整型数组排序）
    printf("%d. 将NumStr排序并输出\n", ++sect_count);
    // 对NumStr按字符串排序
    qsort(NumStr, 5, sizeof(NumStr[0]), Comp);
    // 打印排序后的NumStr
    PrintChar2D((char *)NumStr, 5, 5);
    puts("");


    // 4. 将NumStr合并为一个数组，并以半角逗号进行区分
    printf("%d. 将NumStr合并为一个数组，并以半角逗号进行区分\n", ++sect_count);
    // 合并NumStr并存入char *cb
    char *cb = CombineStrs((char *)NumStr, 5, 5);
    // 打印cb
    puts(cb);
    puts("");

    // 5. 将合并的数组cb以逗号分隔符拆开并输出
    printf("%d. 将合并的数组cb以逗号分隔符拆开并输出\n", ++sect_count);
    SepStrs(cb, ',');
    puts(""); 

    // 在这里是不是还要做点比较安全的事情？
    free(cb);

    // 6. 思考：根据csv文件的格式读取相应内容并存入不同数组
    const char *CsvRecords = "Zoe,29,Hangzhou\nAlice,25,Beijing\nBob,30,Shanghai\nCharlie,22,Guangzhou\nDiana,28,Shenzhen";

    return 0;
}

void PrintChar2D(const char *strs, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%c", *(strs + n * i + j));
        }
        printf("\n");
    }
    puts("");
}

void CharA2IntA(int *arr, const char *strs, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
//        // 希望得到：arr[i]
//        // 第i行的字符串起始位置：strs + i * n
//        int len = strlen(strs + i * n);
//        arr[i] = 0;
//        for(int j = 0; j < len; j++)
//        {
//            arr[i] += (*(strs + i * n + j) - '0') * pow(10, len - j - 1);
//        }
        arr[i] = atoi(strs + i * n);
    }
}

void Char2DCpy(char *new, const char *old, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
//        // 方法1：逐个赋值
//        for(int j = 0; j < n; j++)
//        {
//            *(new + i * n + j) = *(old + i * n + j);
//        }
//        // 方法2：strcpy
//        // 被复制的字符串：old + i * n
//        // 复制给谁：new + i * n
//        strcpy(new + i * n, old + i * n);
//        // 方法3：使用strncpy
//        strncpy(new + i * n, old + i * n, n);
        // Method 4: memcpy
        memcpy(new + i * n, old + i * n, n);
    }
}

int Comp(const void *p1, const void *p2)
{
    return -strcmp((char *)p1, (char *)p2);
}

char *CombineStrs(const char *strs, int m, int n)
{
    int len = strlen(strs);
    char *r = (char *)malloc(len * sizeof(char) + 1); // \0
    sprintf(r, "%s", strs);
    for(int i = 1; i < m; i++)
    {
        len = strlen(strs + i * n);
        r = (char *)realloc(r, len + 1);
        sprintf(r, "%s,%s", r, strs + i * n);
    }
    return r;
}

void SepStrs(char *str, char sep)
{
    char seps[] = {sep};
    char *p = strtok(str, seps);
    while(p != NULL)
    {
        puts(p);
        p = strtok(NULL, seps);
    }
}



