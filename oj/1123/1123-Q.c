#include <stdio.h>

int Strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0') // 使用while来遍历字符，直至到字符串终止符'\0'
        i++;
    return i; // 返回字符串长度
}

int main(void) {
    char s[101];
    if (fgets(s, sizeof(s), stdin) == NULL) return 0;

    size_t n = Strlen(s);
    if (n > 0 && s[n-1] == '\n') {
        s[n-1] = '\0';
        n--;
    }

    for (size_t i = 0; i < n; i++) {
        unsigned char c = s[i];
        if (c >= 'a' && c <= 'z') {
            s[i] = 'a' + (c - 'a' + 2) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            s[i] = 'A' + (c - 'A' + 2) % 26;
        }
    }

    puts(s);
    return 0;
}