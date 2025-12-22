#include <stdio.h>
#include <string.h>

typedef struct {
    int lineno;     // 文本行在文件中的行号
    int Uppers;     // 该行中大写字母字符的个数
    int Lowers;     // 该行中小写字母字符的个数
    int Numbers;    // 该行中数字字符的个数
    int Separators; // 该行中英文分隔字符的个数（含空格、制表符、逗号、句号、分号等5种分隔符）
    int Others;     // 该行中除以上情形外其他字符的个数
} LineInfo, *PLineInfo;

int GetLineInfo(FILE *fp, PLineInfo li) {
    if (fp == NULL || li == NULL || li->lineno <= 0) {
        return 1;
    }
    
    // 初始化统计结果
    li->Uppers = 0;
    li->Lowers = 0;
    li->Numbers = 0;
    li->Separators = 0;
    li->Others = 0;
    
    // 定位到文件开头
    rewind(fp);
    
    char line[256];
    int currentLine = 0;
    
    // 读取到指定行
    while (fgets(line, sizeof(line), fp) != NULL) {
        currentLine++;
        if (currentLine == li->lineno) {
            // 统计该行字符
            for (int i = 0; line[i] != '\0'; i++) {
                char c = line[i];
                if (c == '\n') {
                    // 换行符不做任何统计
                    continue;
                } else if (c >= 'A' && c <= 'Z') {
                    li->Uppers++;
                } else if (c >= 'a' && c <= 'z') {
                    li->Lowers++;
                } else if (c >= '0' && c <= '9') {
                    li->Numbers++;
                } else if (c == ' ' || c == '\t' || c == ',' || c == '.' || c == ';') {
                    li->Separators++;
                } else {
                    li->Others++;
                }
            }
            return 0;
        }
    }
    
    // 指定行号不存在
    return 1;
}

int main() {
    char filename[256];
    int lineNumber;
    
    scanf("%s", filename);
    scanf("%d", &lineNumber);
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    LineInfo li;
    li.lineno = lineNumber;
    
    int result = GetLineInfo(fp, &li);
    
    if (result == 0) {
        printf("%d\n", li.Uppers);
        printf("%d\n", li.Lowers);
        printf("%d\n", li.Numbers);
        printf("%d\n", li.Separators);
        printf("%d\n", li.Others);
    } else {
        printf("Error reading line %d\n", lineNumber);
    }
    
    fclose(fp);
    return 0;
}