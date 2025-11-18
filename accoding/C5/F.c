#include <stdio.h>

// 判断一个自然数是否包含数字 5
int no5(int x) {
    if (x == 0) return 1;
    while (x > 0) {
        if (x % 10 == 5) return 0;
        x /= 10;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int count = 0;
    
    // 枚举所有满足 a <= b <= c 且 a + b + c = n 的三元组
    for (int a = 0; a <= n; a++) {
        if (!no5(a)) continue;  // a 包含数字 5，跳过
        
        for (int b = a; b <= n - a; b++) {
            if (!no5(b)) continue;  // b 包含数字 5，跳过
            
            int c = n - a - b;
            
            // 检查 c 是否满足条件：c >= b 且 c 不包含数字 5
            if (c >= b && no5(c)) {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}