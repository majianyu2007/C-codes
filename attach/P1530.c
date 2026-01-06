#include <stdio.h>
#include <stdlib.h>

int Find_Min(int *, int n);
int Find_Max(int *, int n);
void Adjust_Arr(int **, int, int);
void Swap(int *, int, int (*)(int *, int), int (*)(int *, int));

int main()
{
	int m = 0, n = 0;
	int **arr;
	int i = 0, j = 0;
	scanf("%d%d", &m, &n);

	arr = (int **)malloc(m * sizeof(int *));
	if (arr == NULL) {
		printf("Insufficient Memory!\n");
		exit(1);
	}
	for (i = 0; i < m; i++) {
		arr[i] = (int *)malloc(n * sizeof(int));
		if (arr[i] == NULL) {
			printf("Insufficient Memory!\n");
			exit(1);
		}
	}

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	Adjust_Arr(arr, m, n);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n - 1; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("%d\n", arr[i][j]);
	}

	for (i = 0; i < m; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}

int Find_Max(int *a, int n)
{
	int i = 0;
	int Max = 0;
	for (i = 1; i < n; i++) {
		if (a[i] > a[Max]) {
			Max = i;
		}
	}
	return Max;
}

int Find_Min(int *a, int n)
{
	int i = 0;
	int Min = 0;
	for (i = 1; i < n; i++) {
		if (a[i] < a[Min]) {
			Min = i;
		}
	}
	return Min;
}
