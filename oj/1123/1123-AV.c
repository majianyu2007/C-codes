#include <stdio.h>
#include <string.h>

int isStraight(const char *s) {
    if (strlen(s) != 5) return 0;
    for (int i = 0; i < 4; i++) {
        if (s[i + 1] - s[i] != 1) return 0;
    }
    return 1;
}

int canBeat(const char *hand, const char *played) {
    int handCount[10] = {0};
    int playedLen = strlen(played);
    
    for (int i = 0; hand[i]; i++) {
        handCount[hand[i] - '0']++; // 每个数的牌数
    }
    
    if (playedLen == 5 && isStraight(played)) {
        int startCard = played[0] - '0';
        for (int start = startCard + 1; start <= 5; start++) {
            int canMake = 1;
            for (int j = 0; j < 5; j++) {
                if (handCount[start + j] < 1) {
                    canMake = 0;
                    break;
                }
            }
            if (canMake) return 1;
        }
        return 0;
    }
    
    if (playedLen >= 1 && playedLen <= 4) {
        char card = played[0];
        for (int i = 1; i < playedLen; i++) {
            if (played[i] != card) return 0;
        }
        int cardNum = card - '0';
        for (int c = cardNum + 1; c <= 9; c++) {
            if (handCount[c] >= playedLen) {
                return 1;
            }
        }
        return 0;
    }
    
    return 0;
}

int main() {
    char a[105], b[105];
    while (scanf("%s %s", a, b) == 2) {
        if (canBeat(a, b)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
