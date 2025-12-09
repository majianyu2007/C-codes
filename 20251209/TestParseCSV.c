#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[20];
    int age;
    char city[20];
};


void ParseCSV(const char *csvData, struct Person **persons, int *count);

// ========== 测试框架 ==========
void run_tests();

// ========== 主函数 ==========
int main()
{
    run_tests();
    return 0;
}

void run_tests()
{
    printf("=== CSV 文件解析为结构体测试 ===\n");
    int pass_count = 0;
    int total_count = 0;

    // 测试用例1：正常情况
    printf("\n测试用例1：正常情况\n");
    const char *csv1 = "Zoe,29,Hangzhou\nAlice,25,Beijing\nBob,30,Shanghai\nCharlie,22,Guangzhou\nDiana,28,Shenzhen";

    struct Person *persons1 = NULL;
    int count1 = 0;

    ParseCSV(csv1, &persons1, &count1);

    if (count1 == 5)
    {
        if (strcmp(persons1[0].name, "Zoe") == 0 && persons1[0].age == 29 && strcmp(persons1[0].city, "Hangzhou") == 0)
        {
            if (strcmp(persons1[1].name, "Alice") == 0 && persons1[1].age == 25 && strcmp(persons1[1].city, "Beijing") == 0)
            {
                if (strcmp(persons1[2].name, "Bob") == 0 && persons1[2].age == 30 && strcmp(persons1[2].city, "Shanghai") == 0)
                {
                    if (strcmp(persons1[3].name, "Charlie") == 0 && persons1[3].age == 22 && strcmp(persons1[3].city, "Guangzhou") == 0)
                    {
                        if (strcmp(persons1[4].name, "Diana") == 0 && persons1[4].age == 28 && strcmp(persons1[4].city, "Shenzhen") == 0)
                        {
                            printf("  ✔️ 通过\n");
                            pass_count++;
                        }
                        else
                        {
                            printf("  ❌ 失败: Diana 行错误\n");
                        }
                    }
                    else
                    {
                        printf("  ❌ 失败: Charlie 行错误\n");
                    }
                }
                else
                {
                    printf("  ❌ 失败: Bob 行错误\n");
                }
            }
            else
            {
                printf("  ❌ 失败: Alice 行错误\n");
            }
        }
        else
        {
            printf("  ❌ 失败: Zoe 行错误\n");
        }
    }
    else
    {
        printf("  ❌ 失败: 记录数不正确，期望 5，实际 %d\n", count1);
    }

    free(persons1);
    total_count++;

    // 测试用例2：空数据
    printf("\n测试用例2：空数据\n");
    const char *empty = "";
    struct Person *persons2 = NULL;
    int count2 = 0;

    ParseCSV(empty, &persons2, &count2);

    if (count2 == 0 && persons2 == NULL)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败\n");
    }
    total_count++;

    // 测试用例3：单行
    printf("\n测试用例3：单行数据\n");
    const char *single = "Tom,35,Chengdu";
    struct Person *persons3 = NULL;
    int count3 = 0;

    ParseCSV(single, &persons3, &count3);

    if (count3 == 1 && strcmp(persons3[0].name, "Tom") == 0 && persons3[0].age == 35 && strcmp(persons3[0].city, "Chengdu") == 0)
    {
        printf("  ✔️ 通过\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败\n");
    }

    free(persons3);
    total_count++;

    // 测试用例4：无逗号
    printf("\n测试用例4：异常格式（无逗号）\n");
    const char *invalid = "John18NewYork\nMary22Paris";
    struct Person *persons4 = NULL;
    int count4 = 0;

    ParseCSV(invalid, &persons4, &count4);
    if (count4 == 0 && persons4 == NULL)
    {
        printf("  ✔️ 通过（格式错误，应返回空）\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：应拒绝解析\n");
    }
    total_count++;

    // 测试用例5：字段数量不一致（某行不是3列）
    printf("\n测试用例5：字段数量不一致（第二行只有2列）\n");
    const char *csv5 = "Zoe,29,Hangzhou\nAlice,25\nBob,30,Shanghai";
    struct Person *persons5 = NULL;
    int count5 = 0;

    ParseCSV(csv5, &persons5, &count5);

    if (count5 == 0 && persons5 == NULL)
    {
        printf("  ✔️ 通过（格式错误，应返回空）\n");
        pass_count++;
    }
    else
    {
        printf("  ❌ 失败：应拒绝解析\n");
    }
    total_count++;

    // 汇总结果
    printf("\n=== 测试结果 ===\n");
    printf("通过: %d/%d (%.1f%%)\n", pass_count, total_count, (float)pass_count / total_count * 100);
}


void ParseCSV(const char *csvData, struct Person **persons, int *count)
{
    if (persons == NULL || count == NULL) return;

    *persons = NULL;
    *count = 0;

    // 若 csvData 为空或 NULL，则 return
    if (csvData == NULL || csvData[0] == '\0')
    {
        return;
    }

    int len = strlen(csvData);
    int lines = 0;
    char *temp = NULL;
    temp = (char *)malloc(sizeof(char) * (len + 1));
    if (!temp) free(temp);
    if (temp == NULL) return;
    memcpy(temp, csvData, len + 1);
    for (int i = 0; i < len; i++)
    {
        if (temp[i] == '\n')
        {
            lines++;
        }
    }
    
    if (len > 0 && temp[len - 1] != '\n')
    {
        lines++;
    }

    if (lines == 0) return;

    *persons = (struct Person *)malloc(sizeof(struct Person) * lines);
    if (*persons == NULL) return;

    int index = 0;
    int status = 1;

    char *line;
    char *saveptr = NULL;

    line = strtok_r(temp, "\n", &saveptr);

    while(line && status)
    {
        char *saveptr2 = NULL;
        char *name = strtok_r(line, ",", &saveptr2);
        char *ageStr = strtok_r(NULL, ",", &saveptr2);
        char *city = strtok_r(NULL, ",", &saveptr2);
        char *extra = strtok_r(NULL, ",", &saveptr2);

        if (!name || !ageStr || !city || extra != NULL)
        {
            status = 0;
            break;
        }

        if (strlen(name) == 0 || strlen(name) >= 20)
        {
            status = 0;
            break;
        }

        strcpy((*persons)[index].name, name);

        for (int i = 0; ageStr[i]; i++)
        {
            if (ageStr[i] < '0' || ageStr[i] > '9')
            {
                status = 0;
                break;
            }
        }

        if (status == 0) break;

        (*persons)[index].age = atoi(ageStr);

        if (strlen(city) == 0 || strlen(city) >= 20)
        {
            status = 0;
            break;
        }
        strcpy((*persons)[index].city, city);

        index++;
        line = strtok_r(NULL, "\n", &saveptr);

    }

    free(temp);
    
    if(status == 0 || index == 0)
    {
        free(*persons);
        *persons = NULL;
        *count = 0;
        return;
    }

    *count = index;

    return;
}
