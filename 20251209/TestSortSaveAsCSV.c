#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX_MALLOC 100

char *SortSaveAsCSV(struct Person *persons, int count);

// =================== 测试框架 ===================
void run_tests();

int main()
{
    run_tests();
    return 0;
}

void run_tests()
{
    printf("=== 排序后存储为CSV风格字符串测试 ===\n");
    int pass_count = 0;
    int total_count = 0;

    // 测试用例1：正常情况（多个人，不同年龄）
    printf("\n测试用例1：正常情况\n");
    struct Person people1[] = {
        (struct Person){"Zoe", 29, "Hangzhou"},
        (struct Person){"Alice", 25, "Beijing"},
        (struct Person){"Bob", 30, "Shanghai"}
    };
    char *csv1 = SortSaveAsCSV(people1, 3);

    if (csv1 != NULL && strcmp(csv1, "Alice,25,Beijing\nZoe,29,Hangzhou\nBob,30,Shanghai\n") == 0 && malloc_usable_size(csv1) < MAX_MALLOC)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：输出不正确or内存开辟过大\n");
    }
    free(csv1);
    total_count++;

    // 测试用例2：空数组或NULL输入
    printf("\n测试用例2：空数组或NULL输入\n");
    char *csv2 = SortSaveAsCSV(NULL, 0);
    if (strlen(csv2) == 0)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：应返回空字符串\n");
    }
    total_count++;

    // 测试用例3：单个元素
    printf("\n测试用例3：单个元素\n");
    struct Person person3 = (struct Person){"Tom", 35, "Chengdu"};
    char *csv3 = SortSaveAsCSV(&person3, 1);
    if (csv3 != NULL && strcmp(csv3, "Tom,35,Chengdu\n") == 0 && malloc_usable_size(csv3) < MAX_MALLOC)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：单行输出错误或开辟内存过大\n");
    }
    free(csv3);
    total_count++;

    // 测试用例4：相同年龄（稳定排序）
    printf("\n测试用例4：相同年龄（稳定排序）\n");
    struct Person people4[] = {
        (struct Person){"Zoe", 25, "Hangzhou"},
        (struct Person){"Alice", 25, "Beijing"},
        (struct Person){"Bob", 26, "Shanghai"}
    };
    char *csv4 = SortSaveAsCSV(people4, 3);
    if (csv4 != NULL && strcmp(csv4, "Zoe,25,Hangzhou\nAlice,25,Beijing\nBob,26,Shanghai\n") == 0 && malloc_usable_size(csv4) < MAX_MALLOC)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：排序不稳定或式格错误or开辟内存过大\n");
    }
    free(csv4);
    total_count++;

    // 测试用例5：城市为空字符串
    printf("\n测试用例5：城市为空字符串\n");
    struct Person people5[] = {
        (struct Person){"Zoe", 29, ""},
        (struct Person){"Alice", 25, "Beijing"}
    };
    char *csv5 = SortSaveAsCSV(people5, 2);
    if (csv5 != NULL && strcmp(csv5, "Alice,25,Beijing\nZoe,29,\n") == 0 && malloc_usable_size(csv5) < MAX_MALLOC)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：空城市未正确处理或内存开辟过大\n");
    }
    free(csv5);
    total_count++;

    // 测试用例6：姓名或城市含特殊字符
    printf("\n测试用例6：姓名/城市含特殊字符\n");
    struct Person people6[] = {
        (struct Person){"Li_42", 29, "New-York"},
        (struct Person){"OOP_Programmer", 25, "San-Francisco"}
    };
    char *csv6 = SortSaveAsCSV(people6, 2);
    if (csv6 != NULL && strcmp(csv6, "OOP_Programmer,25,San-Francisco\nLi_42,29,New-York\n") == 0 && malloc_usable_size(csv6) < MAX_MALLOC)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：特殊字符未原样输出或内存开辟过大\n");
    }
    free(csv6);
    total_count++;

    // 测试用例7：负年龄
    printf("\n测试用例7：负年龄\n");
    struct Person people7[] = {
        (struct Person){"Zoe", -5, "Hangzhou"},
        (struct Person){"Alice", 100, "Beijing"}
    };
    char *csv7 = SortSaveAsCSV(people7, 2);
    if (csv7 != NULL && strcmp(csv7, "Zoe,-5,Hangzhou\nAlice,100,Beijing\n") == 0 && malloc_usable_size(csv7) < MAX_MALLOC)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：负数年龄未正确输出或内存开辟过大\n");
    }
    free(csv7);
    total_count++;

    // 汇总结果
    printf("\n=== 测试结果 ===\n");
    printf("通过: %d/%d (%.1f%%)\n", pass_count, total_count, (float)pass_count / total_count * 100);
}


char* SortSaveAsCSV(struct Person *persons, int count)
{
    if (count == 0 || persons == NULL) 
    {
        char *empty = (char *)malloc(1);
        if (empty) 
        {
            empty[0] = '\0';
        }
        return empty;
    }

    struct Person *copy = (struct Person *)malloc(sizeof(struct Person) * count);
    
    if (!copy) return NULL;
    
    memcpy(copy, persons, sizeof(struct Person) * count);

    for (int i = 1; i < count; ++i) {
        struct Person key = copy[i];
        int j = i - 1;
        while (j >= 0 && copy[j].age > key.age) 
        {
            copy[j + 1] = copy[j];
            j--;
        }
        copy[j + 1] = key;
    }

    size_t total_len = 0;
    for (int i = 0; i < count; ++i) 
    {
        total_len += strlen(copy[i].name) + 1 + 5 + 1 + strlen(copy[i].city) + 1;
    }
    char *csv = (char *)malloc(total_len + 1);
    if (!csv) 
    {
        free(copy);
        return NULL;
    }
    csv[0] = '\0';

    char line[64];
    for (int i = 0; i < count; ++i) 
    {
        snprintf(line, sizeof(line), "%s,%d,%s\n", copy[i].name, copy[i].age, copy[i].city);
        strcat(csv, line);
    }
    free(copy);
    return csv;

}

