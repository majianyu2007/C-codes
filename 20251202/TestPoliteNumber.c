#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 函数原型声明
int IsPoliteNumber(int n);
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
    printf("=== 礼貌数判断函数测试（必须使用循环实现） ===\n\n");
    printf("注意：本题必须使用循环方法实现，直接使用2的幂判断将不予通过！\n\n");
    
    int pass_count = 0;
    int total_count = 0;
    int result = 0;
    clock_t start, end;
    double cpu_time_used;
    
    // 测试用例1：明显的礼貌数
    printf("测试1: 明显的礼貌数\n");
    result = IsPoliteNumber(9); // 9 = 4+5 或 2+3+4
    printf("  输入: 9\n");
    printf("  预期: 1\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例2：2的幂次方（非礼貌数）
    printf("\n测试2: 2的幂次方（非礼貌数）\n");
    result = IsPoliteNumber(8); // 8 = 2^3
    printf("  输入: 8\n");
    printf("  预期: 0\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 0 ? "通过" : "失败");
    
    if (result == 0) pass_count++;
    total_count++;
    
    // 测试用例3：边界值1
    printf("\n测试3: 边界值1\n");
    result = IsPoliteNumber(1);
    printf("  输入: 1\n");
    printf("  预期: 0（不能表示为两个或更多连续正整数之和）\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 0 ? "通过" : "失败");
    
    if (result == 0) pass_count++;
    total_count++;
    
    // 测试用例4：边界值3
    printf("\n测试4: 边界值3\n");
    result = IsPoliteNumber(3);
    printf("  输入: 3\n");
    printf("  预期: 1（3=1+2）\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例5：较大的礼貌数
    printf("\n测试5: 较大的礼貌数\n");
    result = IsPoliteNumber(15); // 15=7+8 或 4+5+6 或 1+2+3+4+5
    printf("  输入: 15\n");
    printf("  预期: 1\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例6：质数（通常是礼貌数，除了2）
    printf("\n测试6: 质数（礼貌数）\n");
    result = IsPoliteNumber(7); // 7=3+4
    printf("  输入: 7\n");
    printf("  预期: 1\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 1 ? "通过" : "失败");
    
    if (result == 1) pass_count++;
    total_count++;
    
    // 测试用例7：较大的2的幂次方
    printf("\n测试7: 较大的2的幂次方\n");
    result = IsPoliteNumber(32); // 32=2^5
    printf("  输入: 32\n");
    printf("  预期: 0\n");
    printf("  实际: %d\n", result);
    printf("  结果: %s\n", result == 0 ? "通过" : "失败");
    
    if (result == 0) pass_count++;
    total_count++;
    
    // 测试用例8：大数测试 - 礼貌数
    printf("\n测试8: 大数测试 - 礼貌数\n");
    start = clock();
    result = IsPoliteNumber(1000000); // 1000000是礼貌数
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // 转换为毫秒
    
    printf("  输入: 1000000\n");
    printf("  预期: 1\n");
    printf("  实际: %d\n", result);
    printf("  运行时间: %.2f 毫秒\n", cpu_time_used);
    
    // 检查结果和运行时间
    int time_check = (cpu_time_used > 0.1); // 运行时间应大于0.1毫秒
    int result_check = (result == 1);
    
    if (result_check && time_check)
    {
        printf("  结果: 通过（结果正确且使用了循环）\n");
        pass_count++;
    }
    else if (result_check && !time_check)
    {
        printf("  结果: 失败（结果正确但运行时间过短，可能使用了直接判断）\n");
    }
    else
    {
        printf("  结果: 失败（结果错误）\n");
    }
    total_count++;
    
    // 测试用例9：大数测试 - 非礼貌数
    printf("\n测试9: 大数测试 - 非礼貌数\n");
    start = clock();
    result = IsPoliteNumber(1048576); // 1048576=2^20，不是礼貌数
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // 转换为毫秒
    
    printf("  输入: 1048576\n");
    printf("  预期: 0\n");
    printf("  实际: %d\n", result);
    printf("  运行时间: %.2f 毫秒\n", cpu_time_used);
    
    // 检查结果和运行时间
    time_check = (cpu_time_used > 0.1); // 运行时间应大于0.1毫秒
    result_check = (result == 0);
    
    if (result_check && time_check)
    {
        printf("  结果: 通过（结果正确且使用了循环）\n");
        pass_count++;
    }
    else if (result_check && !time_check)
    {
        printf("  结果: 失败（结果正确但运行时间过短，可能使用了直接判断）\n");
    }
    else
    {
        printf("  结果: 失败（结果错误）\n");
    }
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
    
    // 特别说明
    if (pass_count >= 7 && pass_count < total_count)
    {
        printf("\n注意：部分测试失败可能是因为使用了直接判断方法（检查2的幂次方）。\n");
        printf("本题要求必须使用循环实现，请检查您的实现方法。\n");
    }
}

int IsPoliteNumber(int n)
{
    int test = n, sum = 0;
    for (int i = 1; i <= test; i++)
    {
        for (int j = i; j < test; j++)
        {
            sum += j;
            if (sum == test)
            {
                return 1;
            }
            else if (sum > test)
            {
                break;
            }
        }
        sum = 0;
    }
    return 0;
}


            
