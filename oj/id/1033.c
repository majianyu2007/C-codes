#include <stdio.h>
int main(void)
{
    int N = 0, M = 0;
    if (scanf("%d", &N) != 1 || N <= 0 || N > 100) return 1;
    if (scanf("%d", &M) != 1 || M <= 0 || M >= 65535) return 1;
    
    int result = 0;
    for (int i = 2; i <= N; i++) {
        result = (result + M) % i;
    }
    
    printf("%d\n", result + 1);
    return 0;
}