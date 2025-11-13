#include <stdio.h>

unsigned long long hex2dec(char *s) {
    unsigned long long val = 0;
    int i = 0;
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
    return val;
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

        // 找到操作符
        int i = 0;
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

        // 转十进制
        unsigned long long A = hex2dec(a);
        unsigned long long B = hex2dec(b);

        // 计算
        long long result;
        if (op == '+')
            result = (long long)A + (long long)B;
        else
            result = (long long)A - (long long)B;

        // 输出八进制
        print_oct(result);
    }
    return 0;
}

