#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[20];  /* 居民的姓名 */
    char ID[20];    /* 居民的身份证号码 */
} Person, *PersonPt;

void sortPersons(Person s[], int n)
{
    int i, j;
    Person temp;
    
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (strncmp(s[j].ID + 6, s[j + 1].ID + 6, 8) < 0)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, i;
    Person persons[100];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf(" %[^\n]", persons[i].name);  /* 读取包含空格的姓名 */
        scanf("%s", persons[i].ID);
    }

    sortPersons(persons, n);

    for (i = 0; i < n; i++)
    {
        printf("%s %s\n", persons[i].name, persons[i].ID);
    }

    return 0;
}