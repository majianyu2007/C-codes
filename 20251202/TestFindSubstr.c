#include <stdio.h>
#include <string.h>

// 字符串查找函数声明
int FindSubstring(const char* str, const char* substr);
// 测试函数
void run_tests();

int main() {
    run_tests();
    return 0;
}

// 测试函数
void run_tests() 
{
    printf("=== 字符串查找函数测试 ===\n\n");
    
    int pass_count = 0;
    int total_count = 0;
    
    // 测试用例1：正常情况
    printf("测试1: 正常查找\n");
    int result1 = FindSubstring("Hello world", "world");
    int expected1 = 1;
    printf("  输入: str=\"Hello world\", substr=\"world\"\n");
    printf("  预期: %d, 实际: %d - %s\n", expected1, result1, 
           result1 == expected1 ? "通过" : "失败");
    if (result1 == expected1) 
	    pass_count++;
    total_count++;
    
    // 测试用例2：不存在的情况
    printf("\n测试2: 子串不存在\n");
    int result2 = FindSubstring("Hello world", "test");
    int expected2 = 0;
    printf("  输入: str=\"Hello world\", substr=\"test\"\n");
    printf("  预期: %d, 实际: %d - %s\n", expected2, result2, 
           result2 == expected2 ? "通过" : "失败");
    if (result2 == expected2) 
	    pass_count++;
    total_count++;
    
    // 测试用例3：部分匹配但最后一个字符不匹配
    printf("\n测试3: 部分匹配（最后一个字符不匹配）\n");
    int result3 = FindSubstring("hello world", "hella");
    int expected3 = 0;
    printf("  输入: str=\"hello world\", substr=\"hella\"\n");
    printf("  预期: %d, 实际: %d - %s\n", expected3, result3, 
           result3 == expected3 ? "通过" : "失败");
    if (result3 == expected3) 
	    pass_count++;
    total_count++;
    
    // 测试用例4：开头匹配
    printf("\n测试4: 子串在开头\n");
    int result4 = FindSubstring("hello world", "hello");
    int expected4 = 1;
    printf("  输入: str=\"hello world\", substr=\"hello\"\n");
    printf("  预期: %d, 实际: %d - %s\n", expected4, result4, 
           result4 == expected4 ? "通过" : "失败");
    if (result4 == expected4) 
	    pass_count++;
    total_count++;
    
    // 测试用例5：结尾匹配
    printf("\n测试5: 子串在结尾\n");
    int result5 = FindSubstring("hello world", "world");
    int expected5 = 1;
    printf("  输入: str=\"hello world\", substr=\"world\"\n");
    printf("  预期: %d, 实际: %d - %s\n", expected5, result5, 
           result5 == expected5 ? "通过" : "失败");
    if (result5 == expected5) 
	    pass_count++;
    total_count++;
    
    // 汇总结果
    printf("\n=== 测试结果 ===\n");
    printf("通过: %d/%d (%.1f%%)\n", pass_count, total_count, 
           (float)pass_count/total_count*100);
}

int FindSubstring(const char* str, const char* substr)
{
    if (!str || !substr) return -1;

    int n = strlen(str);
    int m = strlen(substr);

    if (m == 0) return 0;

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && str[i + j] == substr[j])
        {
            j++;
        }
        if (j == m)
        {
            return 1;
        }
    }

    return 0;
}

