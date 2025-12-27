#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义Students结构体
typedef struct {
    char Name[14];    /* 姓名 */
    char ID[10];      /* 学号 */
    char Gender;      /* 性别 */
    int  Age;          /* 年龄 */
    float grade;      /* 成绩 */
} Students;

#define FILENAME "data.dic"
#define MAX_RECORD 256
#define CLASS_NUM 10

// 数据读取函数LoadFile
int LoadFile(Students *student, int start, int max_len);
// 汇总函数Total
void Total(Students *student, int len);
// 按班级分组函数Class
void Class(Students *student, int len);

// 驱动函数
int main() {
    int start, len;
    Students student[MAX_RECORD];

    scanf("%d%d", &start, &len);
    len = LoadFile(student, start, len);
    Total(student,len);
    Class(student,len);
    return 0;
}

size_t GoToLine(FILE * fp, int line)
{
    rewind(fp);
    int i=0;
    if (line==0) return 0;
    char LINE[MAX_RECORD]={0};
    while(fgets(LINE, MAX_RECORD, fp)!=NULL)  {
       i++;
       if(i == line)  break;
    }
    return ftell(fp);
}

// 数据读取函数LoadFile
int LoadFile(Students *student, int start, int max_len) {

    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }
    GoToLine(fp, start - 1);

    int i = 0;
    char line[MAX_RECORD];
    while (fgets(line, sizeof(line), fp)!= NULL && max_len > 0)  {
        sscanf(line,"%[^,],%[^,],%c,%d,%f", student[i].Name, student[i].ID, &student[i].Gender,  &student[i].Age, &student[i].grade);
	i++;
        max_len--;
    }
    fclose(fp);
    return i;
}

// 汇总函数Total
void Total(Students *student, int count) {
    int pass_count = 0;
    int excellent_count = 0;
    float max_grade = student[0].grade;
    float min_grade = student[0].grade;
    int max_node_idx = 0;
    int min_node_idx = 0;
    for(int i=0;i<count;i++) {
        if (student[i].grade >= 60)    pass_count++;
        if (student[i].grade >= 90)    excellent_count++;
        if (student[i].grade > max_grade) {
            max_grade = student[i].grade;
            max_node_idx = i;
        }
        if (student[i].grade < min_grade) {
            min_grade = student[i].grade;
            min_node_idx = i;
        }
    }

    float pass_rate = (float)pass_count / (float)count;
    float excellent_rate = (float)excellent_count / (float)count;
    printf("及格率: %.2f%%\n", pass_rate * 100);
    printf("优秀率: %.2f%%\n", excellent_rate * 100);
    printf("最高成绩: %.2f, 学号: %s, 姓名: %s\n", max_grade, student[max_node_idx].ID, student[max_node_idx].Name);
    printf("最低成绩: %.2f, 学号: %s, 姓名: %s\n", min_grade, student[min_node_idx].ID, student[min_node_idx].Name);
}

int NotPass(char pass_class[][7], int len, char *class)
{
    for(int i=0;i<len;i++)
        if(strcmp(pass_class[i], class) == 0) return 0;
    return 1;
}

// 按班级分组函数Class
void Class(Students *student, int count) {
    int i, len = 0;
    char classes[CLASS_NUM][7]={0};
    for(i=0;i<count;i++) {
        char class_id[7];
        strncpy(class_id, student[i].ID, 6);
        class_id[6] = '\0';
        if (NotPass(classes, len, class_id)) {
            printf("班级: %s\n", class_id);
            int j;
            for(j = 0;j < count; j++) {
                if (strncmp(class_id, student[j].ID, 6) == 0) {
                    printf("学号: %s, 成绩: %.2f\n", student[j].ID, student[j].grade);
                }
            }
            strcpy(classes[len++], class_id);
        }
    }
}

