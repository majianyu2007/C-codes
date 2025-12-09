#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 函数原型声明
int HasPalindromeWord(const char* sentence);
void RunTests();

int main()
{
    RunTests();
    printf("\n按任意键退出...");
    getchar();
    return 0;
}

// 测试函数
void RunTests()
{
    printf("=== 回文单词检测函数测试 ===\n\n");
    
    int pass_count = 0;
    int total_count = 0;
    int result = 0;
    
    // 测试用例1：包含回文单词
    printf("测试1: 包含回文单词\n");
    result = HasPalindromeWord("Madam,this is a test.");
    printf("  输入: \"Madam,this is a test.\"\n");
    printf("  预期: 1 (Madam是回文)\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例2：不包含回文单词
    printf("\n测试2: 不包含回文单词\n");
    result = HasPalindromeWord("Hello world,this is a test.");
    printf("  输入: \"Hello world,this is a test.\"\n");
    printf("  预期: 0\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 0 ? "通过" : "失败");
    
    if (result == 0) pass_count++;
    total_count++;
    
    // 测试用例3：多个回文单词
    printf("\n测试3: 多个回文单词\n");
    result = HasPalindromeWord("mem level");
    printf("  输入: \"mem level\"\n");
    printf("  预期: 1\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例4：空句子
    printf("\n测试4: 空句子\n");
    result = HasPalindromeWord("");
    printf("  输入: \"\"\n");
    printf("  预期: 0\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 0 ? "通过" : "失败");
    
    if (result == 0) pass_count++;
    total_count++;
    
    // 测试用例5：只有标点符号
    printf("\n测试5: 只有标点符号\n");
    result = HasPalindromeWord("!@#$%^&*()");
    printf("  输入: \"!@#$%%^&*()\"\n");
    printf("  预期: 0\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 0 ? "通过" : "失败");
    
    if (result == 0) pass_count++;
    total_count++;
    
    // 测试用例6：单个回文单词
    printf("\n测试6: 单个回文单词\n");
    result = HasPalindromeWord("racecar");
    printf("  输入: \"racecar\"\n");
    printf("  预期: 1\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例7：混合大小写的回文
    printf("\n测试7: 混合大小写的回文\n");
    result = HasPalindromeWord("LeVel is important");
    printf("  输入: \"LeVel is important\"\n");
    printf("  预期: 1 (Level是回文)\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例8：数字和字母混合
    printf("\n测试8: 数字和字母混合\n");
    result = HasPalindromeWord("This is 12321 number");
    printf("  输入: \"This is 12321 number\"\n");
    printf("  预期: 1 (12321是回文)\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
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

int HasPalindromeWord(const char* sentence)
{
    if (sentence == NULL) 
        return -1; // 传空参数处理

    const char* p = sentence;
    while (*p) {

        while (*p && !isalnum(*p)) // 字母与数字可过，略过字符
        {
            p++;
        }
        
        if (*p == '\0') // 如果因为上一个while跳到结尾了就该抓紧终止了
        {
            break;
        }

        const char* start = p;
        
        while (*p && isalnum(*p)) // 来个字母和数字作为起点，读到不是字母和数字和'\0'就停
        {
            p++;
        }
        const char* end = p;

        unsigned int len = end - start;
        if (len >= 2) {
            size_t i = 0, j = len - 1;
            int is_pal = 1;
            while (i < j) {
                char a = (char)tolower(start[i]);
                char b = (char)tolower(start[j]);
                if (a != b) 
                { 
                    is_pal = 0;
                    break; 
                }
                i++; 
                j--;
            }
            if (is_pal) 
                return 1;
        }
    }

    return 0;
}
