#include <stdio.h>
#include <stdbool.h>

long long hex2dec(char *s) {
    bool negative = false;
    int i = 0;
    
    // 检查是否有负号
    if (s[0] == '-') {
        negative = true;
        i = 1;
    }
    
    unsigned long long val = 0;
    while (s[i] != '\0') {
        val = val * 16;
        char c = s[i];
        if (c >= '0' && c <= '9')
            val += c - '0';
        else if (c >= 'A' && c <= 'F')
            val += c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            val += c - 'a' + 10;
        i++;
    }
    
    return negative ? -(long long)val : (long long)val;
}

void print_oct(long long x) {
    if (x == 0) {
        printf("0\n");
        return;
    }

    if (x < 0) {
        printf("-");
        x = -x;
    }

    char buf[50];
    int idx = 0;

    while (x > 0) {
        buf[idx++] = (x % 8) + '0';
        x /= 8;
    }

    // 倒序输出
    for (int i = idx - 1; i >= 0; i--)
        putchar(buf[i]);
    putchar('\n');
}

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        char s[40];
        scanf("%s", s);

        // 找到操作符（从第二个字符开始查找，避免把负号当作运算符）
        int i = (s[0] == '-') ? 1 : 0;  // 如果开头是负号，从第二个字符开始
        int op_pos = -1;
        char op = 0;

        while (s[i] != '\0') {
            if (s[i] == '+' || s[i] == '-') {
                op = s[i];
                op_pos = i;
                break;
            }
            i++;
        }

        // 分割成左右两个十六进制数
        char a[40], b[40];
        int p = 0;

        // 左边
        for (int j = 0; j < op_pos; j++)
            a[p++] = s[j];
        a[p] = '\0';

        // 右边
        p = 0;
        for (int j = op_pos + 1; s[j] != '\0'; j++)
            b[p++] = s[j];
        b[p] = '\0';

        // 转十进制（现在支持负数）
        long long A = hex2dec(a);
        long long B = hex2dec(b);

        // 计算
        long long result;
        if (op == '+')
            result = A + B;
        else
            result = A - B;

        // 输出八进制
        print_oct(result);
    }
    return 0;
}

