#include <stdio.h>
#include <string.h>

typedef struct {
    int lineno;
    int Uppers;
    int Lowers;
    int Numbers;
    int Separators;
    int Others;
} LineInfo, *PLineInfo;

int GetLineInfo(FILE *fp, PLineInfo li) {
    if (fp == NULL || li == NULL || li->lineno <= 0) {
        return 1;
    }
    
    li->Uppers = 0;
    li->Lowers = 0;
    li->Numbers = 0;
    li->Separators = 0;
    li->Others = 0;
    
    rewind(fp);
    
    char line[256];
    int currentLine = 0;
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        currentLine++;
        if (currentLine == li->lineno) {
            for (int i = 0; line[i] != '\0'; i++) {
                char c = line[i];
                if (c == '\n') {
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