#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SortStrings(char **strs, int n);

// ========== 测试框架 ==========
void run_tests();

// ========== 主函数 ==========
int main() {
    run_tests();
    return 0;
}

void run_tests()
{
    printf("=== 字符串数组双重排序测试 ===\n");
    int pass_count = 0;
    int total_count = 0;

    // 测试用例1：正常情况
    printf("\n测试用例1：正常情况\n");
    char *strs1[] = {malloc(4), malloc(4), malloc(4)};
    strcpy(strs1[0], "cba");
    strcpy(strs1[1], "fed");
    strcpy(strs1[2], "abc");
    SortStrings(strs1, 3);
    if (strcmp(strs1[0], "abc") == 0 && strcmp(strs1[1], "abc") == 0 && strcmp(strs1[2], "def") == 0)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败: 实际 [%s, %s, %s]\n", strs1[0], strs1[1], strs1[2]);
    }
    free(strs1[0]);
    free(strs1[1]);
    free(strs1[2]);
    total_count++;

    // 测试用例2：包含空字符串
    printf("\n测试用例2：包含空字符串\n");
    char *strs2[] = {malloc(1), malloc(5), malloc(6)};
    strcpy(strs2[0], "");
    strcpy(strs2[1], "dcba");
    strcpy(strs2[2], "hello");
    SortStrings(strs2, 3);
    if (strcmp(strs2[0], "") == 0 && strcmp(strs2[1], "abcd") == 0 && strcmp(strs2[2], "ehllo") == 0)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败\n");
    }
    free(strs2[0]);
    free(strs2[1]);
    free(strs2[2]);
    total_count++;

    // 测试用例3：单字符字符串
    printf("\n测试用例3：单字符字符串\n");
    char *strs3[] = {malloc(2), malloc(2), malloc(2)};
    strcpy(strs3[0], "b");
    strcpy(strs3[1], "a");
    strcpy(strs3[2], "c");
    SortStrings(strs3, 3);
    if (strcmp(strs3[0], "a") == 0 && strcmp(strs3[1], "b") == 0 && strcmp(strs3[2], "c") == 0)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败\n");
    }
    free(strs3[0]);
    free(strs3[1]);
    free(strs3[2]);
    total_count++;

    // 测试用例4：大规模动态示例（课堂原题）
    printf("\n测试用例4：大规模动态示例（课堂原题）\n");
    int m = 26;
    char **strs4 = (char**)malloc(m * sizeof(char*));
    for (int i = 0; i < m; i++)
    {
        strs4[i] = (char*)malloc((i + 2) * sizeof(char));
        for (int j = 0; j <= i; j++)
        {
            strs4[i][j] = 'z' - j;
        }
        strs4[i][i + 1] = '\0';
    }

    SortStrings(strs4, m);

    int valid = 1;
    for (int i = 0; i < m; i++)
    {
        size_t len = strlen(strs4[i]);
        for (size_t j = 0; j + 1 < len; j++)
        {
            if (strs4[i][j] > strs4[i][j + 1])
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            break;
        }
    }

    if (valid)
    {
        for (int i = 0; i < m - 1; i++)
        {
            if (strcmp(strs4[i], strs4[i + 1]) > 0)
            {
                valid = 0;
                break;
            }
        }
    }

    if (valid)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败\n");
    }

    for (int i = 0; i < m; i++)
    {
        free(strs4[i]);
    }
    free(strs4);
    total_count++;

    // 测试用例5：n为0且strs为NULL
    printf("\n测试用例5：n为0且strs为NULL\n");
    SortStrings(NULL, 0);
    printf("  ✔️ 无异常，通过\n");
    pass_count++;
    total_count++;

    printf("\n=== 测试结果 ===\n");
    printf("通过: %d/%d (%.1f%%)\n", pass_count, total_count, (float)pass_count / total_count * 100);
}

void SortStrings(char **strs, int n)
{

    if (strs == NULL || n <= 0) // 传入失败或字符串小于等于0则退出函数 
    {
        return;
    }

    for (int i = 0; i < n; i++) // 对第i个字符串进行操作
    {
        int len = strlen(strs[i]);
        // 冒泡排序
        for (int j = 0; j < len - 1; j++)
        {
            for (int k = j + 1; k < len; k++) 
            {
                if (strs[i][j] > strs[i][k]) 
                {
                    char temp = strs[i][j];
                    strs[i][j] = strs[i][k];
                    strs[i][k] = temp;
                }
            }
        }
    }

    // 冒泡排序
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (strcmp(strs[i], strs[j]) > 0) 
            {
                char *temp = strs[i];
                strs[i] = strs[j];
                strs[j] = temp;
            }
        }
    }

}
