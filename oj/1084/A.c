#include <stdio.h>
#include <stdlib.h>

/* 构建杨辉三角形 */
unsigned int *create_yanghui(size_t);
/* 构建第n行(n>=3)的杨辉三角形单行数据 */
unsigned int *createline(unsigned int *, int);
/* 销毁杨辉三角形 */
void destory_yanghui(unsigned int *);
/* 输出杨辉三角形 */
void print_yanghui(unsigned int *, size_t);

int main()
{
    unsigned int *pyh = NULL;
    int num;

    scanf("%d", &num);
    pyh = create_yanghui(num);
    print_yanghui(pyh, num);
    destory_yanghui(pyh);
    pyh = NULL;

    return 0;
}

unsigned int *create_yanghui(size_t num)
{
	size_t total_size;
	int i;
	unsigned int *p = NULL;

	total_size = (num * num + num) / 2;
	p = (unsigned int *)malloc(total_size * sizeof(unsigned int));
	if (p == NULL) {
		printf("Not enough row's memory!\n");
		exit(1);
	}

	p[0] = p[1] = p[2] = 1;
	for (i = 3; i <= num; i++) {
		createline(p, i);
	}
	return p;
}

void destory_yanghui(unsigned int *pyh)
{
	free(pyh);
}

void print_yanghui(unsigned int *pyh, size_t num)
{
	int i, j;

	for (i = 1; i <= num; i++) {
		for (j = 1; j <= i; j++) {
			printf("%d ",
			       pyh[((i - 1) * (i - 1) + i) / 2 + (j - 1)]);
		}
		printf("\n");
	}
}

unsigned int *createline(unsigned int *p, int line)
{
    if (line < 3) return NULL;
    unsigned int *prev = &p[(line-1)*(line-2)/2];
    unsigned int *new = &p[line*(line-1)/2];
    if (prev == NULL) return NULL;
    if (new == NULL) return NULL;

    new[0] = 1;
    new[line - 1] = 1;

    for(int i = 1; i < line - 1; i++)
    {
        new[i] = prev[i] + prev[i-1];
    }

    return new;
}
