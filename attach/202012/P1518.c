#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

void GotoLine(FILE *, int n);
void Run(FILE *, FILE *, int, int);
void reverse(char *src);
void sort_name(char **Name, int n);

int main()
{
    FILE *fin, *fout;
    int start, end;
    fin = fopen("student.dic","r");
    fout = fopen("student_new.txt","w");
    if (fin == NULL || fout == NULL)
    {
        puts("Open File Error!\n");
        return -1;
    }
    scanf("%d%d", &start, &end);
    Run(fin, fout, start, end);
    fclose(fout);
    fclose(fin);
    return 0;
}
/* 注意：以上代码中不在7处错误之内，在提交OJ时不要包含在内 */

void Run(FILE *fin, FILE *fout, int m, int n)
{
    char **Name;
    int i;

    Name = (char **)malloc((n - m + 1) * sizeof(char *));
    GotoLine(fin, m);
    for(i = 0; i <= n - m; i++) {
        Name+i = (char *)malloc(MAX_LEN * sizeof(char)); 
        fgets(Name+i, MAX_LEN, fin); 
        Name[i][strlen(Name[i])-1] = '\0'; 
    } 

    sort_name(Name, n - m + 1); 
    for(i = 0; i <= n - m; i++) { 
        if (strlen(Name[i])>1) {
            fputs(Name[i], fout); 
            puts(Name[i]);
        }
        free(Name+i); 
    }
    free(Name); 
}

void GotoLine(FILE *fp, int n) 
{ 
    int i; 
    char temp[MAX_LEN]; 

    rewind(fp);
    for(i=0;i < n-1 && !feof(fp);i++)
        fgets(temp, MAX_LEN, fp);
}

void reverse(char *src)
{
    char *temp;
    int i, j, t = 0;

    for(i = 0; i < strlen(src); i++)  {
        if(src[i] == ' ') break;
    }
    for(j = i+1; j < strlen(src); j++)  {
        temp[t++] = src[j];
    }
    temp[t++] = ' ';
    for(j = 0; j < i; j++) {
        temp[t++] = src[j];
    }
    
    strcpy(src, temp);
}

void sort_name(char **Name, int n)
{
    int i, j;
    char *temp;

    for(i = 0; i < n; i++) {
        reverse(Name[i]);
    }

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n -i; j++)
        {
            if(strcmp(Name[j], Name[j+1]))
            {
                temp = Name[j];
                Name[j] = Name[j+1];
                Name[j+1] = temp;
            }
        }
    }
}
