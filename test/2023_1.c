#include <stdio.h>
#include <math.h>

int main() {
    int count[3] = {0, 0, 0}; // 计数三个元素
    int ch;

    while ((ch = getchar()) != '\n') {
        if (ch == 'a') 
        {
            count[0]++;
        }
        else if (ch == 'b') 
        {
            count[1]++;
        }
        else if (ch == 'c') 
        {
            count[2]++;
        }
        else
        {
            continue;
        }
    }

    int total = count[0] + count[1] + count[2];
    if (total == 0) {  // 没有输入有效字符时，进行异常处理
        printf("0.000\n");
        return 0;
    }

    double H = 0.0;

    for (int i = 0; i < 3; i++) {
        if (count[i] > 0) 
        {
            double p = (double)count[i] / total;
            H -= p * log2(p);
        }
    }

    printf("%.3f\n", H);
    return 0;
}
