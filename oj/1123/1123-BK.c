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

/* 将字符串s中全部字母变为小写 */
void lowcase(char *s)
{
    while (*s)
    {
        if (*s >= 'A' && *s <= 'Z')
        {
            *s = *s - 'A' + 'a';
        }
        s++;
    }
}

/* 判断word1与word2是否互为变位词，是返回1，否则返回0 */
int areAnagrams(const char *word1, const char *word2)
{
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int count[26] = {0};
    int i;

    if (len1 != len2)
    {
        return 0;
    }

    /* 复制并转换为小写 */
    char *s1 = (char *)malloc(len1 + 1);
    char *s2 = (char *)malloc(len2 + 1);
    strcpy(s1, word1);
    strcpy(s2, word2);
    lowcase(s1);
    lowcase(s2);

    /* 统计字母出现次数 */
    for (i = 0; i < len1; i++)
    {
        if (s1[i] >= 'a' && s1[i] <= 'z')
        {
            count[s1[i] - 'a']++;
        }
        if (s2[i] >= 'a' && s2[i] <= 'z')
        {
            count[s2[i] - 'a']--;
        }
    }

    free(s1);
    free(s2);

    /* 检查所有字母计数是否为0 */
    for (i = 0; i < 26; i++)
    {
        if (count[i] != 0)
        {
            return 0;
        }
    }

    return 1;
}

/* 返回文本串text中包含的子串word及其变位词的个数 */
int countAnagrams(const char *text, const char *word)
{
    int textLen = strlen(text);
    int wordLen = strlen(word);
    int count = 0;
    int i;

    if (wordLen > textLen || wordLen == 0)
    {
        return 0;
    }

    /* 逐个提取与单词长度相等的子字符串 */
    for (i = 0; i <= textLen - wordLen; i++)
    {
        /* 提取子串 */
        char *sub = (char *)malloc(wordLen + 1);
        strncpy(sub, text + i, wordLen);
        sub[wordLen] = '\0';

        /* 判断是否为变位词 */
        if (areAnagrams(sub, word))
        {
            count++;
        }

        free(sub);
    }

    return count;
}