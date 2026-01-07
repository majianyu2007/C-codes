#include <stdio.h>
#include <stdlib.h>

int MinInsert(int *pnums, int m, int k);
int cmp(const void *a, const void *b);

int main() {
    int m, k;

    printf("请输入数组元素个数 m：");
    scanf("%d", &m);

    int nums[100];  // m < 50，足够用
    printf("请输入 %d 个正整数：\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &nums[i]);
    }

    printf("请输入要填充的数量 k：");
    scanf("%d", &k);

    int result = MinInsert(nums, m, k);
    printf("MinInsert 返回值 = %d\n", result);

    return 0;
}

int MinInsert(int *pnums, int m, int k)
{
    int left = 0, right = 0, sum = 0, i = 0;
    qsort(pnums, m, sizeof(int), cmp);
judge:
    if(i < m)
    {
        right = pnums[i];
        int gap = right - left - 1;
        if(gap > 0)
        {
            if(k <= gap)
            {
                sum += (left * 2 + 1 + k) * k / 2;
                return sum;
            }
            else
            {
                sum += (left + right) * gap / 2;
                k -= gap;
                left = right;
                i++;
                goto judge;
            }
        }
        else
        {
            left = right;
            i++;
            goto judge;
        }
    }
    else
    {
        if(k != 0)
        {
            sum += (left * 2 + 1 + k) * k / 2;
            return sum;
        }
        else
        {
            return sum;
        }
    }
}

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
