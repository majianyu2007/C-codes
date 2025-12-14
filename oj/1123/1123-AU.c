#include <stdio.h>
#include <string.h>

int delSubStr(char *src, char *sub, char *result) {
    int count = 0;
    int subLen = strlen(sub);
    int srcLen = strlen(src);
    int resultIndex = 0;
    
    if (subLen == 0) 
    {
        strcpy(result, src);
        return 0;
    }
    
    int i = 0;
    while (i < srcLen) 
    {
        int match = 1;
        if (i + subLen <= srcLen) 
        {
            for (int j = 0; j < subLen; j++) 
            {
                if (src[i + j] != sub[j]) 
                {
                    match = 0;
                    break;
                }
            }
        }
        else 
        {
            match = 0;
        }
        
        if (match) 
        {
            count++;
            i += subLen;
        } 
        else 
        {
            result[resultIndex++] = src[i];
            i++;
        }
    }
    
    result[resultIndex] = '\0';
    return count;
}

int main() {
    char src[1000], sub[1000], result[1000];
    
    scanf("%s", src);
    scanf("%s", sub);
    
    int count = delSubStr(src, sub, result);
    
    printf("%s\n", result);
    printf("%d\n", count);
    
    return 0;
}
