#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student 
{
    char name[21];  // 姓名，最多20字符 + '\0'
    int age;        // 年龄
    int id;         // 学号
};

// 你需要实现
void LoadAndSortStudents(char mode, struct Student **stus, int *n);

int main() 
{
    char mode = getchar();
    struct Student *students;
    int n;
    LoadAndSortStudents(mode, &students, &n);
    for (int i = 0; i < n; i++)
    {
        printf("id: %d, name: %s, age: %d\n", students[i].id, students[i].name, students[i].age);
    }
    return 0;
}

int cmpByNameThenId(const void *a, const void *b)
{
    const struct Student *s1 = (const struct Student *)a;
    const struct Student *s2 = (const struct Student *)b;

    int nameCmp = strcmp(s1->name, s2->name);
    if (nameCmp != 0) 
    {
        return nameCmp;
    }

    return s1->id - s2->id;
}

int cmpByAgeThenId(const void *a, const void *b)
{
    const struct Student *s1 = (const struct Student *)a;
    const struct Student *s2 = (const struct Student *)b;

    if (s1->age != s2->age)
    {
        return s1->age - s2->age;
    }

    return s1->id - s2->id;
}

int cmpById(const void *a, const void *b)
{
    const struct Student *s1 = (const struct Student *)a;
    const struct Student *s2 = (const struct Student *)b;

    return s1->id - s2->id;
}


void LoadAndSortStudents(char mode, struct Student **stus, int *n)
{
    FILE *fp;
    fp = fopen("stuInfo.dat", "rb");
    if (fp == NULL) return;
    fread(n, sizeof(int), 1, fp);
    *stus = (struct Student *)malloc(sizeof(struct Student) * (*n));
    if (*stus == NULL)
    {
        fclose(fp);
        return;
    }
    fread(*stus, sizeof(struct Student), *n, fp);
    
    switch(mode) {
        case 'n': goto n;
        case 'a': goto a;
        case 'i': goto i;
        default: fclose(fp); free(*stus); return;
    }
n:
    qsort(*stus, *n, sizeof(struct Student), cmpByNameThenId);
    fclose(fp);
    return;
a:
    qsort(*stus, *n, sizeof(struct Student), cmpByAgeThenId);
    fclose(fp);
    return;
i:
    qsort(*stus, *n, sizeof(struct Student), cmpById);
    fclose(fp);
    return;
}

