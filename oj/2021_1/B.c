#include <stdio.h>

long long hex_to_dec(const char *s) {
    long long x = 0;
    while (*s) {
        char c = *s++;
        if (c >= '0' && c <= '9') 
        {
            x = x * 16 + (c - '0');
        }
        else if (c >= 'A' && c <= 'F') 
        {
            x = x * 16 + (c - 'A' + 10);
        }
        else if (c >= 'a' && c <= 'f') 
        {
            x = x * 16 + (c - 'a' + 10);
        }
    }
    return x;
}

void dec_to_oct(long long val, char *out) {

    char buf[64];
    int i = 0;
    unsigned long long x = (unsigned long long)val;

    if (x == 0) 
    { 
        out[0] = '0'; out[1] = '\0'; return; 
    }

    while (x > 0) // 取余法生成八进制（倒序）
    {                         
        buf[i++] = '0' + (x % 8);
        x /= 8;
    }

    // 翻转写入输出
    for (int k = 0; k < i; ++k) 
    {
        out[k] = buf[i - 1 - k];
    }
    out[i] = '\0';
}

int main() {
    int n;                                 
    scanf("%d", &n);

    while (n--) {
        char expr[64], op;
        char ans[64];

        scanf("%s", expr);

        // 找运算符
        int i = 0;
        while (expr[i] != '+' && expr[i] != '-') i++;
        op = expr[i];

    // 拆成 A, B
    expr[i] = '\0';

    long long A = hex_to_dec(expr);
    long long B = hex_to_dec(expr + i + 1);

        long long C = (op == '+') ? (A + B) : (A - B);

        dec_to_oct(C, ans);
        printf("%s\n", ans);
    }
    return 0;
}
