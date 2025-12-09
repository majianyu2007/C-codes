#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数原型声明
char* ReplaceAll(const char* original, const char* target, const char* replacement);
int StringsEqual(const char* str1, const char* str2);
void RunTests();
void TestMemoryLeak();

int main()
{
    RunTests();
    TestMemoryLeak();
    
    printf("\n按任意键退出...");
    getchar();
    
    return 0;
}

// 辅助函数：比较两个字符串是否相等
int StringsEqual(const char* str1, const char* str2)
{
    if (str1 == NULL && str2 == NULL)
    {
        return 1;
    }
    
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }
    
    return strcmp(str1, str2) == 0;
}

// 测试函数
void RunTests()
{
    printf("=== 字符串替换函数测试 ===\n\n");
    
    int pass_count = 0;
    int total_count = 0;
    char* result = NULL;
    char* expected = NULL;
    
    // 测试用例1：正常情况 - 单次替换
    printf("测试1: 正常替换（单次出现）\n");
    result = ReplaceAll("I like apples", "apples", "oranges");
    expected = "I like oranges";
    printf("  输入: original=\"I like apples\", target=\"apples\", replacement=\"oranges\"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 测试用例2：多次替换
    printf("\n测试2: 多次替换\n");
    result = ReplaceAll("I like apples, apples are delicious.", "apples", "oranges");
    expected = "I like oranges, oranges are delicious.";
    printf("  输入: original=\"I like apples, apples are delicious.\", target=\"apples\", replacement=\"oranges\"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 测试用例3：目标子串不存在
    printf("\n测试3: 目标子串不存在\n");
    result = ReplaceAll("I like apples", "bananas", "oranges");
    expected = "I like apples";
    printf("  输入: original=\"I like apples\", target=\"bananas\", replacement=\"oranges\"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 测试用例4：原始字符串为空
    printf("\n测试4: 原始字符串为空\n");
    result = ReplaceAll("", "apples", "oranges");
    expected = "";
    printf("  输入: original=\"\", target=\"apples\", replacement=\"oranges\"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 测试用例5：替换为空字符串（删除操作）
    printf("\n测试5: 替换为空字符串（删除）\n");
    result = ReplaceAll("Hello World", "o", "");
    expected = "Hell Wrld";
    printf("  输入: original=\"Hello World\", target=\"o\", replacement=\"\"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 测试用例6：连续出现目标子串（重点测试）
    printf("\n测试6: 连续出现目标子串\n");
    result = ReplaceAll("aaaa", "aa", "b");
    expected = "bb";
    printf("  输入: original=\"aaaa\", target=\"aa\", replacement=\"b\"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 测试用例7：特殊字符
    printf("\n测试7: 特殊字符\n");
    result = ReplaceAll("a-b-c-d", "-", " ");
    expected = "a b c d";
    printf("  输入: original=\"a-b-c-d\", target=\"-\", replacement=\" \"\n");
    printf("  预期: \"%s\"\n", expected);
    printf("  实际: \"%s\"\n", result ? result : "NULL");
    printf("  结果: %s\n", StringsEqual(result, expected) ? "通过" : "失败");
    
    if (StringsEqual(result, expected))
    {
        pass_count++;
    }
    total_count++;
    result = NULL;
    
    // 汇总结果
    printf("\n=== 测试结果 ===\n");
    printf("通过: %d/%d (%.1f%%)\n", pass_count, total_count, 
           (float)pass_count / total_count * 100);
    
    if (pass_count == total_count)
    {
        printf("所有测试通过！\n");
    }
    else
    {
        printf("有 %d 个测试失败\n", total_count - pass_count);
    }
}

// 内存泄漏检查辅助函数
void TestMemoryLeak()
{
    printf("\n=== 内存泄漏检查 ===\n");
    
    // 测试多次替换，检查是否有内存泄漏
    char* results[3];
    
    results[0] = ReplaceAll("test test test", "test", "TEST");
    results[1] = ReplaceAll("hello world", "hello", "Hi");
    results[2] = ReplaceAll("a b c d", " ", "");
    
    printf("替换结果:\n");
    
    for (int i = 0; i < 3; i++)
    {
        printf("  结果%d: %s\n", i + 1, results[i] ? results[i] : "NULL");
        free(results[i]); // 正确释放内存
        results[i] = NULL;
    }
    
    printf("若results均能正常输出，则释放基本正确\n");
}

// 字符串替换函数实现
char* ReplaceAll(const char* original, const char* target, const char* replacement)
{
    // 检查参数是否为空
    if (original == NULL || target == NULL || replacement == NULL)
    {
        return NULL;
    }
    
    // 计算各字符串长度
    int orig_len = strlen(original);
    int target_len = strlen(target);
    int repl_len = strlen(replacement);
    
    // 如果目标字符串为空，返回原字符串的副本
    if (target_len == 0)
    {
        char* result = (char*)malloc((orig_len + 1)*sizeof(char));
        
        if (result == NULL)
        {
            return NULL;
        }
        
        strcpy(result, original);
        result[orig_len] = '\0';
        return result;
    }
    
    // 计算需要替换的次数
    int count = 0;
    const char* pos = original;
    
    while ((pos = strstr(pos, target)) != NULL) // strstr的用法在课本P486
    {
        count++;
        pos += target_len; // 跳过已找到的目标字符串
    }
    
    // 计算新字符串长度
    int new_len = orig_len + count * (repl_len - target_len);
    char* result = (char*)malloc((new_len + 1)*sizeof(char));
    
    if (result == NULL)
    {
        return NULL;
    }
    
    // 执行替换操作
    char* current = result;
    const char* start = original;
    const char* found;
    
    while ((found = strstr(start, target)) != NULL)
    {
        // 复制目标字符串之前的部分
        int prefix_len = found - start;
        if (prefix_len > 0)
        {
            strncpy(current, start, prefix_len);
            current += prefix_len;
        }
        
        // 复制替换字符串
        if (repl_len > 0)
        {
            strcpy(current, replacement);
            current += repl_len;
        }
        
        // 移动到下一个位置
        start = found + target_len;
    }
    
    // 复制剩余部分
    strcpy(current, start);
    result[new_len] = '\0';
    return result;
}
