#include <stdio.h>
#include <string.h>

int CountLine(FILE *fp, int n) {
    if (fp == NULL || n <= 0) {
        return 0;
    }
    
    // Key press counts for each letter a-z
    // abc(2) def(3) ghi(4) jkl(5) mno(6) pqrs(7) tuv(8) wxyz(9)
    int keyPresses[26] = {
        1, 2, 3,        // a, b, c -> 2
        1, 2, 3,        // d, e, f -> 3
        1, 2, 3,        // g, h, i -> 4
        1, 2, 3,        // j, k, l -> 5
        1, 2, 3,        // m, n, o -> 6
        1, 2, 3, 4,     // p, q, r, s -> 7
        1, 2, 3,        // t, u, v -> 8
        1, 2, 3, 4      // w, x, y, z -> 9
    };
    
    char line[201];
    int currentLine = 0;
    
    // Read lines until we reach line n
    while (fgets(line, sizeof(line), fp) != NULL) {
        currentLine++;
        if (currentLine == n) {
            int count = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (line[i] >= 'a' && line[i] <= 'z') {
                    count += keyPresses[line[i] - 'a'];
                } else if (line[i] == ' ') {
                    count += 1;  // Space requires 1 key press
                }
                // Ignore all other characters (uppercase, digits, symbols, \n, \t, etc.)
            }
            return count;
        }
    }
    
    // Line n doesn't exist
    return 0;
}

int main() {
    // 创建测试文件
    FILE *fp = fopen("test.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "hello world\n");
        fprintf(fp, "abc def\n");
        fprintf(fp, "test message\n");
        fclose(fp);
    }
    
    // 测试 CountLine 函数
    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    
    int n;
    printf("请输入行号: ");
    scanf("%d", &n);
    
    int result = CountLine(fp, n);
    printf("第 %d 行的按键次数: %d\n", n, result);
    
    fclose(fp);
    
    // 也可以直接测试多行
    printf("\n--- 测试所有行 ---\n");
    for (int i = 1; i <= 3; i++) {
        fp = fopen("test.txt", "r");
        if (fp != NULL) {
            printf("第 %d 行按键次数: %d\n", i, CountLine(fp, i));
            fclose(fp);
        }
    }
    
    return 0;
}