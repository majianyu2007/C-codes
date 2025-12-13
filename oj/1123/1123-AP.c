#include <stdio.h>
#include <string.h>

int main() {
    char str[25];
    unsigned char font[10];
    FILE *fp;
    int i, j, k, len;
    
    scanf("%s", str);
    len = strlen(str);
    
    fp = fopen("ASC10x8.dic", "rb");
    if (fp == NULL) {
        return 1;
    }
    
    for (i = 0; i < 10; i++) {
        for (j = 0; j < len; j++) {
            int offset = (str[j] - 0x20) * 10 + i;
            fseek(fp, offset, SEEK_SET);
            fread(&font[0], 1, 1, fp);
            
            for (k = 7; k >= 0; k--) {
                if (font[0] & (1 << k)) {
                    printf("#");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    
    fclose(fp);
    return 0;
}