#include <stdio.h>
#include <stdlib.h>

struct PA
{
    int len;
    int *arr;
};

struct PF
{
    int len;
    int arr[];
};

int main()
{
    struct PA *pa = (struct PA *)malloc(sizeof(struct PA));
    int len = 5;
    pa->len = len;
    pa->arr = (int *)malloc(sizeof(int) * pa->len);
    free(pa->arr);
    free(pa);

    struct PF *pf = (struct PF *)malloc(sizeof(int) + sizeof(int) * len);
    pf->len = len;
    for(int i = 0; i < pf->len; i++)
        pf->arr[i] = i;
    for(int i = 0; i < pf->len; i++)
        printf("%d ", pf->arr[i]);
    putchar('\n');
    free(pf);
    return 0;
}
