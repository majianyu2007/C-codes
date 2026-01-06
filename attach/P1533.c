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
	PStudent t;
	int i, len;

	fp = fopen(FileName, "w");
	while (i < start) {
		fread(&t, sizeof(Student), 1, fp);
		i++;
	}
	len = fread(&a, sizeof(Student), end - start + 1, fp);
	fclose(fp);
	return len;
}

void Print(PStudent a, int len)
{
	int i;

	printf("   学号   | 姓名 |       身份证     | 成绩 |排名\n");
	printf("----------------------------------------------------\n");
	for (i = 0; i < len; i++)
		printf("%10s|%-8s|%18s|%6.2f|%3d\n", a[i].Sno, a[i].Name,
		       a[i].Id, a[i].Score, a[i].Ranking);
	printf("----------------------------------------------------\n");
}
