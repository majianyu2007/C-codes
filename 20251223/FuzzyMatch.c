#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// 你需要实现的函数
int FuzzyMatchLine(const char *filename, int i, const char *pattern);

int main()
{
    int i;
    char pattern[51];  // 题目说明 pattern 长度 ≤ 50

    if (scanf("%d", &i) != 1)
    {
        printf("No\n");
        return 0;
    }

    // 跳过换行符
    getchar();

    if (fgets(pattern, sizeof(pattern), stdin) == NULL)
    {
        printf("No\n");
        return 0;
    }

    // 去除 fgets 读入的换行符（如果存在）
    size_t len = strlen(pattern);
    if (len > 0 && pattern[len - 1] == '\n')
    {
        pattern[len - 1] = '\0';
    }

    int result = FuzzyMatchLine("strings.txt", i, pattern);

    if (result == 1)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }

    return 0;
}


int FuzzyMatchLine(const char *filename, int i, const char *pattern)
{
    if (pattern[0] == '\0') return 1;
    if (i < 1) return 0;
    char line[100];
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) return 0;
    for (int j = 1; j <= i; j++)
    {
        if (fgets(line, sizeof(line), fp) == NULL) 
        {
            fclose(fp);
            return 0;
        }
    }
    for (int k = 0; line[k] != '\0'; k++)
    {
        line[k] = tolower((unsigned char)line[k]);
    }
    char *pattern_temp;
    pattern_temp = NULL;
    pattern_temp = (char *)malloc(strlen(pattern) * sizeof(char));
    memcpy(pattern_temp, pattern, strlen(pattern));
    for(int l = 0; pattern_temp[l] != '\0'; l++)
    {
        pattern_temp[l] = tolower((unsigned char)pattern_temp[l]);
    }
    if (strstr(line, pattern_temp) != NULL) 
    {
        free(pattern_temp);
        fclose(fp);
        return 1;
    }
    free(pattern_temp);
    fclose(fp);
    return 0;
}


