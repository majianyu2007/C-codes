#include <stdio.h>       // 标准输入/输出函数库（scanf/printf 等）
#include <ctype.h>       // 字符分类与转换（这里用到 isdigit 判断是否为数字字符）

long long hex_to_dec(const char *s) {       // 将不带 0x 前缀的十六进制字符串（假定非负）转换为十进制 long long
    long long x = 0;                        // 累加的十进制结果
    while (*s) {                            // 遍历直到遇到字符串结束符 '\0'
        char c = *s++;                      // 取当前字符，并将指针前移一位
        if (isdigit(c)) x = x * 16 + (c - '0');             // '0'..'9' 转为 0..9 并累加
        else if (c >= 'A' && c <= 'F') x = x * 16 + (c - 'A' + 10); // 'A'..'F' 转为 10..15 并累加
        else if (c >= 'a' && c <= 'f') x = x * 16 + (c - 'a' + 10); // 'a'..'f' 转为 10..15 并累加
        // 其他字符不处理（题目保证输入合法，不会出现）
    }
    return x;                               // 返回转换结果
}

void dec_to_oct(long long val, char *out) { // 将十进制 long long 数值转换为八进制字符串，写入 out 缓冲区
    char buf[64];                           // 临时反向存放八进制字符的缓冲区
    int neg = 0, i = 0;                     // neg 标记是否为负数；i 为缓冲区下标
    unsigned long long x;                   // 用无符号保存绝对值，避免最小负数取绝对值溢出

    if (val < 0) {                          // 如果是负数
        neg = 1;                            // 记录负号
        x = (unsigned long long)(-(val + 1)) + 1ULL; // 安全取绝对值：避免对 LLONG_MIN 直接取 -val 溢出
    } else {                                 // 非负数
        x = (unsigned long long)val;        // 直接转换为无符号数
    }

    if (x == 0) {                           // 特判 0 的情况
        out[0] = '0';                       // 输出字符 '0'
        out[1] = '\0';                      // 字符串结束符
        return;                             // 返回
    }

    while (x > 0) {                         // 反复除以 8，取余得到八进制的每一位（低位在前）
        buf[i++] = '0' + (x % 8);           // 保存当前八进制位的字符表示
        x /= 8;                             // 继续处理更高位
    }

    if (neg) buf[i++] = '-';                // 若原数为负，追加负号（此时在反向缓冲区的末尾）

    // 反向写入输出：由于 buf 中是低位在前、符号在末尾，这里需要倒序复制到 out
    int k = 0;                              // 输出字符串下标
    while (i--) out[k++] = buf[i];          // 倒序拷贝至 out
    out[k] = '\0';                          // 末尾加上字符串结束符
}

int main() {                                // 程序入口
    int n;                                  // 测试用例数量
    scanf("%d", &n);                       // 读取用例个数（题目保证输入合法，未显式检查返回值）

    while (n--) {                           // 依次处理每组输入
        char expr[64], a[64], b[64], op;    // expr：形如 "1A+2B" 的表达式；a/b：左右操作数；op：运算符
        char ans[64];                       // 存放八进制转换结果的字符串

        scanf("%s", expr);                 // 读入当前表达式（无空格）

        // 找运算符
        int i = 0;                          // 从开头开始扫描
        while (expr[i] != '+' && expr[i] != '-') i++; // 找到第一个 '+' 或 '-' 作为运算符（不支持操作数本身带符号）
        op = expr[i];                       // 记录运算符

        // 拆成 A, B
        expr[i] = '\0';                    // 在运算符处截断，左侧成为独立字符串
        snprintf(a, sizeof(a), "%s", expr);           // 复制左操作数字符串到 a
        snprintf(b, sizeof(b), "%s", expr + i + 1);   // 复制右操作数字符串到 b（跳过运算符）

        long long A = hex_to_dec(a);        // 左操作数：十六进制转十进制
        long long B = hex_to_dec(b);        // 右操作数：十六进制转十进制

        long long C = (op == '+') ? (A + B) : (A - B); // 根据运算符进行加或减

        dec_to_oct(C, ans);                 // 将结果转换为八进制字符串
        printf("%s\n", ans);               // 输出一行结果
    }
    return 0;                               // 正常结束程序
}
