#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FileName "Student.dic"

typedef struct StuInfo {
	char Sno[12];
	char Name[20];
	char Id[20];
	float Score;
	int Ranking;
} Student, *PStudent;

int Compare(const void *, const void *);
void OrderStu(PStudent stu_array, int len);
int ReadFile(PStudent a, int start, int end);
void Print(PStudent stu_array, int len);

int main()
{
	PStudent a;
	int len;
	int start, end;

	scanf("%d%d", &start, &end);
	len = end - start + 1;
	a = (PStudent) malloc(len * sizeof(Student));
	len = ReadFile(a, start, end);
	OrderStu(a, len);
	Print(a, len);
	free(a);
	return 0;
}

int ReadFile(PStudent a, int start, int end)
{
	FILE *fp;
	int len;

	fp = fopen(FileName, "rb");
	if (fp == NULL) {
		return 0;
	}

	fseek(fp, (long)start * sizeof(Student), SEEK_SET);
	len = fread(a, sizeof(Student), end - start + 1, fp);
	fclose(fp);
	return len;
}

int Compare(const void *pa, const void *pb)
{
	const Student *a = (const Student *) pa;
	const Student *b = (const Student *) pb;
	int birth_cmp;

	if (a->Score > b->Score)
		return -1;
	if (a->Score < b->Score)
		return 1;

	birth_cmp = strncmp(a->Id + 6, b->Id + 6, 8);
	if (birth_cmp < 0)
		return -1;
	if (birth_cmp > 0)
		return 1;

	return 0;
}

void OrderStu(PStudent stu_array, int len)
{
	qsort(stu_array, len, sizeof(Student), Compare);
}

void Print(PStudent a, int len)
{
    int i;

    /* 请不要修改输出格式相关的内容 */
    printf("   学号   |  姓名  |       身份证     | 成绩 |排名\n");
    printf("----------------------------------------------------\n");
    for(i=0;i < len;i++)
        printf("%10s|%-8s|%18s|%6.2f|%3d\n",a[i].Sno, a[i].Name, a[i].Id, a[i].Score, a[i].Ranking);
    printf("----------------------------------------------------\n");
}
