#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20
#define MAX_FRUIT_LEN 20

typedef struct{
    char name[MAX_NAME_LEN];
    float in;
    float out;
}FInfo, *pFInfo;

int loadStock(pFInfo, const char *);
void sortAndSaveStock(pFInfo, int, char *);

int main(int argc, char *argv[])
{
    FInfo fruitStock[MAX_FRUIT_LEN];

    if (argc < 3)
    {
        printf("Usage: %s <STOCK_FILE.txt> <SAVE_FILE.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* read stock information from txt file */
    int n = loadStock(fruitStock, argv[1]);

    if ( n > 0)  sortAndSaveStock(fruitStock, n, argv[2]);
    return 0;
}


int loadStock(pFInfo stocks, const char *fname)
{
    if (fname == NULL) return 0;
    FILE *fp = NULL;
    fp = fopen(fname, "r");
    int n = 0;
    while (fscanf(fp, "%19s %f %f", stocks[n].name, &stocks[n].in, &stocks[n].out) == 3) {
        n++;
    }
    fclose(fp);
    return n;
}

int cmp(const void *a, const void *b)
{
    const FInfo *x = (const FInfo *)a;
    const FInfo *y = (const FInfo *)b;

    double r1 = x->in - x->out;
    double r2 = y->in - y->out;
    if (r2 > r1) return 1;
    if (r2 < r1) return -1;
    return 0;
}
void sortAndSaveStock(pFInfo stocks, int n, char *fname)
{
    qsort(stocks, n, sizeof(FInfo), cmp);
    FILE *fp = NULL;
    fp = fopen(fname, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%s %.1f %.1f", stocks[i].name, stocks[i].in, stocks[i].out);
        if (i != n - 1) fprintf(fp, "\n");
    }
    fclose(fp);
}
