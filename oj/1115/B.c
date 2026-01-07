#include <stdio.h>

// 你要提交的函数
int getEAN13(char *ean);

int main() {
    char ean[20];

    printf("请输入条形码前12位：\n");

    // 支持从文件重定向读取，也支持手动输入
    while (scanf("%s", ean) != EOF) {
        int check = getEAN13(ean);
        printf("输入：%s  → 校验码 = %d\n", ean, check);
        printf("继续输入下一条（Ctrl+D 结束）：\n");
    }

    return 0;
}

int getEAN13(char *ean)
{
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0, x = 0;
    for(int i = 0; i < 12; i++)
    {
        if(i % 2 == 0)
        {
            r3 += ean[i] - '0';
            continue;
        }
        else
        {
            r1 += ean[i] - '0';
            continue;
        }
    }
    
    r2 = r1 * 3;
    r4 = r2 + r3;
    x = (10 - (r4 % 10)) % 10;
    return x;
}
