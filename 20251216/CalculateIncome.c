#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    int id;
    char name[30];  // 实际上是 "Lastname Firstname"
    double income;
};

// 你需要完成的函数
double SumIncomeByLastname(struct Person *people, int n, const char *lastname);
double SumIncomeByIDList(struct Person *people, int n, int *id_list, int id_count);

// 用于测试
void Test(struct Person *people, int n);

int main(void) {
    int n;
    scanf("%d", &n);
    getchar(); // 清除换行符

    struct Person *people = (struct Person *)malloc(n * sizeof(struct Person));
    for (int i = 0; i < n; i++) {
        // 读取一行
        char line[100];
        if (!fgets(line, sizeof(line), stdin)) 
            break;
        
        // 解析行并存入结构体的相应数据中
        int id;
        char lastname[20], firstname[20];
        double income;

        sscanf(line, "%d %s %s %lf", &id, lastname, firstname, &income);

        people[i].id = id;
        people[i].income = income;
        snprintf(people[i].name, sizeof(people[i].name),"%s %s", lastname, firstname);

    }

    Test(people, n);
    free(people);
    return 0;
}

void Test(struct Person *people, int n) {
    // 0. 测试输出全部信息
    for(int i = 0; i < n; i++)
        printf("%d %s %f\n", people[i].id, people[i].name, people[i].income);

    // 1. 测试姓氏 "Zhang"
    printf("=== 测试: 姓氏 \"Zhang\" ===\n");
    printf("%.2f\n", SumIncomeByLastname(people, n, "Zhang"));

    // 2. 测试姓氏 "Li"
    printf("=== 测试: 姓氏 \"Li\" ===\n");
    printf("%.2f\n", SumIncomeByLastname(people, n, "Li"));

    // 3. 测试姓氏 "Torres"（假设存在）
    printf("=== 测试: 姓氏 \"Torres\" ===\n");
    printf("%.2f\n", SumIncomeByLastname(people, n, "Torres"));

    // 4. 测试不存在的姓氏 "Minese"
    printf("=== 测试: 姓氏 \"Minese\" (不存在) ===\n");
    printf("%.2f\n", SumIncomeByLastname(people, n, "Minese"));

    // 5. 测试完整名 "Zhang San"（不应匹配，因为只比对姓）
    printf("=== 测试: 姓氏 \"Zhang San\" (完整名) ===\n");
    printf("%.2f\n", SumIncomeByLastname(people, n, "Zhang San"));

    // 6. 测试 ID 列表：1001 ~ 1100 全部 ID
    printf("=== 测试: ID 1001~1100 全部 ===\n");
    int all_ids[100];
    for (int i = 0; i < 100; i++) {
        all_ids[i] = 1001 + i;
    }
    printf("%.2f\n", SumIncomeByIDList(people, n, all_ids, 100));

    // 7. 测试 ID 列表：1001~1100 的奇数 ID
    printf("=== 测试: ID 1001~1100 奇数 ===\n");
    int odd_ids[50];
    int count = 0;
    for (int i = 1001; i <= 1100; i += 2) {
        odd_ids[count++] = i;
    }
    printf("%.2f\n", SumIncomeByIDList(people, n, odd_ids, count));

    // 8. 测试 ID 列表：1001~1100 的偶数 ID
    printf("=== 测试: ID 1001~1100 偶数 ===\n");
    int even_ids[50];
    count = 0;
    for (int i = 1002; i <= 1100; i += 2) {
        even_ids[count++] = i;
    }
    printf("%.2f\n", SumIncomeByIDList(people, n, even_ids, count));
}

double SumIncomeByLastname(struct Person *people, int n, const char *lastname)
{
    if (n <= 0) return -1;
    if (!people) return -1;
    if (!lastname) return -1;

    double sum = 0.0;
    int len = strlen(lastname);

    for (int i = 0; i < n; i++)
    {
        if (strncmp(people[i].name, lastname, len) == 0 && people[i].name[len] == ' ')
        {
            sum += people[i].income;
        }
    }
    return sum;
}


double SumIncomeByIDList(struct Person *people, int n, int *id_list, int id_count)
{
    double sum = 0.0;
    if ( people == NULL ) return -1;
    if ( n <= 0 ) return -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < id_count; j++)
        {
            if ( people[i].id == id_list[j] ) 
            {
                sum += people[i].income;
                break;
            }
        }
    }
    return sum;
}

