#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN           10  //合法单词的长度上限
#define E_STRING_LEN  -1  //单词长度不合法
#define E_MEMORY      -2  //内存分配错误

#define FREE(v) do { if (v) { free(v); v = NULL; } } while(0)

// 动态分配内存给每个字符串指针
int init(char **strArray,int n);
// 找到最小和最大串并交换到合适位置
void change(char ** strArray, int n);

void swap(char **a, char **b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

int main()
{
    char **pWords;
    int n,i;
    scanf("%d\n",&n);
    pWords=(char **)malloc(n*sizeof(char *));
    if (pWords == NULL)
    {
        printf("memory error\n");
        exit(0);
    }
    int r = init(pWords,n);
    switch (r) {
        case E_STRING_LEN:
            printf("word length error.\n");
            exit(0);
        case E_MEMORY:
            printf("memory error.\n");
            exit(0);
    }

    change(pWords,n);
    // 输出结果
    for (i = 0; i < n; i++)
    {
        puts(pWords[i]);
    }
    // 释放分配的内存
    for (i = 0; i < n; i++)
    {
        FREE(pWords[i]);
    }
    FREE(pWords);
    return 0;
}


int init(char ** strArray, int n)
{
    for(int i = 0; i < n; i++)
    {
        char temp[LEN+2];
        if (fgets(temp, LEN+2, stdin) == NULL) return E_STRING_LEN;
        int len = strlen(temp);
        
        int has_newline = (temp[len-1] == '\n');
        
        if (!has_newline && len == LEN+1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            return E_STRING_LEN;
        }
        
        if (has_newline) {
            temp[len-1] = '\0';
            len--;
        }
        
        if (len == 0) return E_STRING_LEN;
        
        char *p = (char *)malloc((len + 1) * sizeof(char));
        if (p == NULL) return E_MEMORY;
        strcpy(p, temp);
        strArray[i] = p;
    }
    return 0;
}

void change(char ** strArray, int n)
{
    int min_idx = 0;
    int max_idx = 0;
    
    for (int i = 1; i < n; i++)
    {
        if (strcmp(strArray[i], strArray[min_idx]) < 0) {
            min_idx = i;
        }
        if (strcmp(strArray[i], strArray[max_idx]) > 0) {
            max_idx = i;
        }
    }
    swap(&strArray[0], &strArray[min_idx]);
    if (max_idx == 0) {
        max_idx = min_idx;
    }
    swap(&strArray[n-1], &strArray[max_idx]);
}

