#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validUtf8(int *data, int len);
int countLeadingOnes(int b);

int main(void) {
    int cap = 128, n = 0;
    int *a = (int *)malloc(sizeof(int) * cap);
    if (!a) return 1;

    // 读到 EOF 为止
    int x;
    while (scanf("%d", &x) == 1) {
        if (n >= cap) {
            cap *= 2;
            int *na = (int *)realloc(a, sizeof(int) * cap);
            if (!na) { free(a); return 1; }
            a = na;
        }
        a[n++] = x;
    }

    if (n == 0) {  // 没输入
        free(a);
        return 0;
    }

    int *data = a;
    int len = n;

    // 兼容：若输入为 “len 后跟 len 个数”
    if (n >= 2) {
        int first = a[0];
        if (first >= 0 && first == n - 1) {
            len = first;
            data = a + 1;
        }
    }

    int ans = validUtf8(data, len);
    printf("%d\n", ans);

    free(a);
    return 0;
}

int countLeadingOnes(int b) {
    b &= 0xFF;
    int cnt = 0;
    for (int k = 7; k >= 0; --k) {
        if ((b >> k) & 1) cnt++;
        else break;
    }
    return cnt;
}

int validUtf8(int *data, int len)
{
    int i = 0;
    while (i < len) {
        int numBytes = countLeadingOnes(data[i]);
        
        if (numBytes == 0) {
            i++;
            continue;
        }
        
        if (numBytes == 1 || numBytes > 4) {
            return 0;
        }
        
        if (i + numBytes > len) {
            return 0;
        }
        
        for (int j = 1; j < numBytes; j++) {
            int byte = data[i + j] & 0xFF;
            if ((byte >> 6) != 0b10) {
                return 0;
            }
        }
        
        i += numBytes;
    }
    
    return 1;
}


