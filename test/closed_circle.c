#include <stdio.h>

int main(void)
{
    int low, high, cnt;
    if ((scanf("%d %d", &low, &high)) != 2 || low > high)
    {
        printf("Invalid input\n");
        return 1;
    }
    cnt = 0;

    for (int i = low; i <= high; i++)
    {
        int num;
        if (i < 0)
        {
            num = -i;
        }
        else if (i == 0)
        {
            cnt++;
            continue;
        }
        else
        {
            num = i;
        }
        while(num)
        {
            int temp = num % 10;
            switch (temp)
            {
                case 0:
                case 6:
                case 9:
                    cnt++;
                    break;
                case 8:
                    cnt += 2;
                    break;
                default:
                    break;
            }
            num /= 10;
        }
    }
    printf("%d\n", cnt);
    return 0;
}