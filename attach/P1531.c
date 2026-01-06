#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int x, y, z;
} Point;

typedef enum { XAXIS, YAXIS, ZAXIS } AXIS;
typedef int (*CallBack) (int, int);

int compareA(int, int);
int compareD(int, int);
Point *input(int n);
void selection_sort(Point * a, int n, char mode, AXIS ch);
CallBack setmode(char mode);

int main()
{
	int i, ch, n;
	char k;

	scanf("%d%c%d", &n, &k, &ch);
	Point *pt = input(n);
	selection_sort(pt, n, k, ch);
	for (i = 0; i < n; i++)
		printf("%d %d %d\n", pt[i].x, pt[i].y, pt[i].z);
	free(pt);
	return 0;
}

Point *input(int n)
{
	int i;
	Point *a;
	a = (Point *) malloc(n * sizeof(Point));
	for (i = 0; i < n; i++)
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
	return a;
}

int compareA(int x, int y)
{
	return x > y;
}

int compareD(int x, int y)
{
	return x < y;
}

CallBack setmode(char mode)
{
	if (mode == 'D')
		return compareD;
	else
		return compareA;
}
