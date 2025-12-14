#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 255

int countAnagrams(const char *, const char *); /* 统计变位词个数 */
int areAnagrams(const char *, const char *); /* 变位词判断 */

/* 辅助函数 */
int read_line(char *, int); /* 读入不超过指定长度的字符串 */
void lowcase(char *); /* 将字符串变为小写 */

int main()
{
    char text[STR_LEN + 1] = {'\0'};
    char word[STR_LEN + 1] = {'\0'};
    int cnt = 0;

    read_line(text, STR_LEN);
    read_line(word, STR_LEN);

    cnt = countAnagrams(text, word);

    printf("The text is \"%s\".\n", text);
    printf("The word is \"%s\".\n", word);
    printf("The count of anagrams is %d.\n", cnt);

    return 0;
}

/* 函数实现 */
/* 读入一行不超过指定长度的字符串 */
int read_line(char *str, int n)
{
    int ch, i = 0;

    /* 读入字符，直到遇到换行符 */
    while ((ch = getchar()) != '\n' && ch != '\r' && ch != EOF)
    {
        if (i < n) /* 最大字符数 */
        {
            str[i++] = ch;
        }
    }
    str[i] = '\0'; /* 添加空字符'\0' */
    return i;      /* 返回读入的字符数 */
}

void lowcase(char *s)
{
    while (*s) {
        unsigned char ch = (unsigned char)*s;
        *s = (char)tolower(ch);
        s++;
    }
}

int areAnagrams(const char *word1, const char *word2)
{
    int len1 = (int)strlen(word1);
    int len2 = (int)strlen(word2);
    if (len1 != len2) return 0;

    int cnt[256] = {0};

    for (int i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)word1[i];
        unsigned char c2 = (unsigned char)word2[i];
        c1 = (unsigned char)tolower(c1);
        c2 = (unsigned char)tolower(c2);
        cnt[c1]++;
        cnt[c2]--;
    }

    for (int i = 0; i < 256; i++) {
        if (cnt[i] != 0) return 0;
    }
    return 1;
}

int countAnagrams(const char *text, const char *word)
{
    int textLen = (int)strlen(text);
    int wordLen = (int)strlen(word);
    if (wordLen == 0 || wordLen > textLen) return 0;

    int count = 0;

    // 关键：不允许重叠命中。命中一次就跳过 wordLen
    for (int i = 0; i <= textLen - wordLen; ) {
        char sub[256];                 // 题目保证长度不超过255
        memcpy(sub, text + i, wordLen);
        sub[wordLen] = '\0';

        if (areAnagrams(sub, word)) {
            count++;
            i += wordLen;              // 不重叠
        } else {
            i += 1;
        }
    }

    return count;
}

