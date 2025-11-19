#include <stdio.h>

int is_Prime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// 检查一个数是否只有质因数2（即是否为2的幂次）
int is_PowerOf2(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

int main(void)
{
    int x;
    scanf("%d", &x);
    int count = 0;
    
    // 用数组记录访问过的状态（假设数值不会太大）
    int visited[10000000] = {0};
    
    while (1)
    {
        // 检查是否到达质因数只有2的数
        if (is_PowerOf2(x))
        {
            printf("%d %d\n", x, count);
            return 0;
        }
        
        // 检查是否进入循环（访问过且不是2的幂次）
        if (x < 10000000 && visited[x])
        {
            printf("En taro\n");
            return 0;
        }
        
        if (x < 10000000)
            visited[x] = 1;
        
        if (is_Prime(x))
        {
            x = (x | (x * 2)) + 1;
        }
        else
        {
            // 找到最小的非1正因数并除以它
            for (int j = 2; j <= x; j++)
            {
                if (x % j == 0)
                {
                    x = x / j;
                    break;
                }
            }
        }
        count++;
    }
    
    return 0;
}