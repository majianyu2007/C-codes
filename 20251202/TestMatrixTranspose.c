#include <stdio.h>
#include <stdlib.h>

// 函数原型声明
int** TransMat(int** matrix, int m, int n);
int** CreateMatrix(int m, int n);
void FreeMatrix(int** matrix, int m);
void PrintMatrix(int** matrix, int m, int n);
int CompareMatrices(int** mat1, int m1, int n1, int** mat2, int m2, int n2);
void RunTests();

int main()
{
    RunTests();
    printf("\n测试完成，按任意键退出...");
    getchar();
    return 0;
}

// 创建指定大小的矩阵并填充测试数据
int** CreateMatrix(int m, int n)
{
    if (m <= 0 || n <= 0) return NULL;
    
    int** matrix = (int**)malloc(m * sizeof(int*));
    if (matrix == NULL) return NULL;
    
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL)
        {
            // 分配失败，释放已分配的内存
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
        
        // 填充测试数据：matrix[i][j] = i * n + j + 1
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = i * n + j + 1;
        }
    }
    
    return matrix;
}

// 释放矩阵内存
void FreeMatrix(int** matrix, int m)
{
    if (matrix == NULL) return;
    
    for (int i = 0; i < m; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// 打印矩阵
void PrintMatrix(int** matrix, int m, int n)
{
    if (matrix == NULL)
    {
        printf("矩阵为空\n");
        return;
    }
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

// 比较两个矩阵是否相等
int CompareMatrices(int** mat1, int m1, int n1, int** mat2, int m2, int n2)
{
    if (m1 != m2 || n1 != n2) return 0;
    if (mat1 == NULL || mat2 == NULL) return 0;
    
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

// 测试函数
void RunTests()
{
    printf("=== 矩阵转置函数测试 ===\n\n");
    
    int pass_count = 0;
    int total_count = 0;
    
    // 测试用例1：2x3矩阵转置
    printf("测试1: 2x3矩阵转置\n");
    int** original1 = CreateMatrix(2, 3);
    printf("原始矩阵(2x3):\n");
    PrintMatrix(original1, 2, 3);
    
    int** result1 = TransMat(original1, 2, 3);
    printf("转置结果(3x2):\n");
    PrintMatrix(result1, 3, 2);
    
    // 验证结果：创建期望的转置矩阵
    int** expected1 = CreateMatrix(3, 2);
    if (expected1 != NULL)
    {
        expected1[0][0] = 1; expected1[0][1] = 4;
        expected1[1][0] = 2; expected1[1][1] = 5;
        expected1[2][0] = 3; expected1[2][1] = 6;
    }
    
    int test1_pass = CompareMatrices(result1, 3, 2, expected1, 3, 2);
    printf("结果: %s\n\n", test1_pass ? "通过" : "失败");
    
    if (test1_pass) pass_count++;
    total_count++;
    
    // 释放内存
    FreeMatrix(original1, 2);
    FreeMatrix(result1, 3);
    FreeMatrix(expected1, 3);
    
    // 测试用例2：1x1矩阵转置
    printf("测试2: 1x1矩阵转置\n");
    int** original2 = CreateMatrix(1, 1);
    printf("原始矩阵(1x1):\n");
    PrintMatrix(original2, 1, 1);
    
    int** result2 = TransMat(original2, 1, 1);
    printf("转置结果(1x1):\n");
    PrintMatrix(result2, 1, 1);
    
    int test2_pass = (result2 != NULL) && (result2[0][0] == original2[0][0]);
    printf("结果: %s\n\n", test2_pass ? "通过" : "失败");
    
    if (test2_pass) pass_count++;
    total_count++;
    
    // 释放内存
    FreeMatrix(original2, 1);
    FreeMatrix(result2, 1);
    
    // 测试用例3：3x1矩阵转置（列向量）
    printf("测试3: 3x1矩阵转置（列向量）\n");
    int** original3 = CreateMatrix(3, 1);
    printf("原始矩阵(3x1):\n");
    PrintMatrix(original3, 3, 1);
    
    int** result3 = TransMat(original3, 3, 1);
    printf("转置结果(1x3):\n");
    PrintMatrix(result3, 1, 3);
    
    // 验证结果
    int test3_pass = 1;
    if (result3 != NULL)
    {
        test3_pass = (result3[0][0] == 1) && (result3[0][1] == 2) && (result3[0][2] == 3);
    }
    else
    {
        test3_pass = 0;
    }
    printf("结果: %s\n\n", test3_pass ? "通过" : "失败");
    
    if (test3_pass) pass_count++;
    total_count++;
    
    // 释放内存
    FreeMatrix(original3, 3);
    FreeMatrix(result3, 1);
    
    // 测试用例4：1x4矩阵转置（行向量）
    printf("测试4: 1x4矩阵转置（行向量）\n");
    int** original4 = CreateMatrix(1, 4);
    printf("原始矩阵(1x4):\n");
    PrintMatrix(original4, 1, 4);
    
    int** result4 = TransMat(original4, 1, 4);
    printf("转置结果(4x1):\n");
    PrintMatrix(result4, 4, 1);
    
    // 验证结果
    int test4_pass = 1;
    if (result4 != NULL)
    {
        test4_pass = (result4[0][0] == 1) && (result4[1][0] == 2) && 
                     (result4[2][0] == 3) && (result4[3][0] == 4);
    }
    else
    {
        test4_pass = 0;
    }
    printf("结果: %s\n\n", test4_pass ? "通过" : "失败");
    
    if (test4_pass) pass_count++;
    total_count++;
    
    // 释放内存
    FreeMatrix(original4, 1);
    FreeMatrix(result4, 4);
    
    // 测试用例5：方阵转置（3x3）
    printf("测试5: 3x3方阵转置\n");
    int** original5 = CreateMatrix(3, 3);
    printf("原始矩阵(3x3):\n");
    PrintMatrix(original5, 3, 3);
    
    int** result5 = TransMat(original5, 3, 3);
    printf("转置结果(3x3):\n");
    PrintMatrix(result5, 3, 3);
    
    // 验证方阵转置：对角线不变，其他元素对称交换
    int test5_pass = 1;
    if (result5 != NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (result5[i][j] != original5[j][i])
                {
                    test5_pass = 0;
                    break;
                }
            }
            if (!test5_pass) break;
        }
    }
    else
    {
        test5_pass = 0;
    }
    printf("结果: %s\n\n", test5_pass ? "通过" : "失败");
    
    if (test5_pass) pass_count++;
    total_count++;
    
    // 释放内存
    FreeMatrix(original5, 3);
    FreeMatrix(result5, 3);
    
    // 汇总结果
    printf("=== 测试结果汇总 ===\n");
    printf("通过测试: %d/%d\n", pass_count, total_count);
    printf("成功率: %.1f%%\n", (float)pass_count / total_count * 100);
    
    if (pass_count == total_count)
    {
        printf("🎉 所有测试通过！\n");
    }
    else
    {
        printf("❌ 有 %d 个测试失败\n", total_count - pass_count);
    }
}

int** TransMat(int** matrix, int m, int n)
{
    int **arr;
    arr = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(m * sizeof(int));
        if(arr[i] == NULL)
            return NULL;
        for(int j = 0; j < m; j++)
        {
            arr[i][j] = matrix[j][i];
        }
    }
    return arr;
}

