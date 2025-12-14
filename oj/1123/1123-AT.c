#include <stdio.h>
#include <string.h>
#include <ctype.h>

int CheckPhoneNum(char *num) {
    if (num == NULL || strlen(num) == 0) {
        return 1;
    }
    
    int len = strlen(num);
    int dashCount = 0;
    int dashPos[2] = {-1, -1};
    
    // 统计减号数量和位置
    for (int i = 0; i < len; i++) {
        if (num[i] == '-') {
            if (dashCount < 2) {
                dashPos[dashCount] = i;
            }
            dashCount++;
        }
    }
    
    if (dashCount < 1 || dashCount > 2) {
        return 1;
    }
    
    int areaCodeLen, prefixStart, prefixLen, validNumStart, validNumLen;
    
    if (dashCount == 1) {
        // 没有地区码
        areaCodeLen = 0;
        prefixStart = 0;
        prefixLen = dashPos[0];
        validNumStart = dashPos[0] + 1;
        validNumLen = len - validNumStart;
    } else {
        // 有地区码
        areaCodeLen = dashPos[0];
        prefixStart = dashPos[0] + 1;
        prefixLen = dashPos[1] - dashPos[0] - 1;
        validNumStart = dashPos[1] + 1;
        validNumLen = len - validNumStart;
    }
    
    // 检查地区码
    if (areaCodeLen < 0 || areaCodeLen > 4) {
        return 1;
    }
    for (int i = 0; i < areaCodeLen; i++) {
        if (!isdigit(num[i])) {
            return 1;
        }
    }
    
    // 检查前缀
    if (prefixLen != 3) {
        return 1;
    }
    if (num[prefixStart] == '0') {
        return 1;
    }
    for (int i = prefixStart; i < prefixStart + 3; i++) {
        if (!isdigit(num[i])) {
            return 1;
        }
    }
    
    // 检查有效号码
    if (validNumLen != 4) {
        return 1;
    }
    for (int i = validNumStart; i < validNumStart + 4; i++) {
        if (!isdigit(num[i])) {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    char num[100];
    while (scanf("%s", num) != EOF) {
        printf("%d\n", CheckPhoneNum(num));
    }
    return 0;
}
