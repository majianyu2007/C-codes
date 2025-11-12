#include <stdio.h>

int main(void)
{
    char ch = 'A';
    short int si = 0;
    int i = 0;
    long int li = 0;
    float f = 0.0f;
    double d = 0.0;

    printf("size of char=%zu\n", sizeof(ch));
    printf("size of short=%zu\n", sizeof(si));
    printf("size of int=%zu\n", sizeof(i));
    printf("size of long int=%zu\n", sizeof(li));
    printf("size of float=%zu\n", sizeof(f));
    printf("size of double=%zu\n", sizeof(d));

    return 0;
}
