#include <stdio.h>

struct Employee {
    char name[21];
    char id[21];
    int empNum;
    double salary;
};

int main() {
    struct Employee emp;
    
    scanf("%s", emp.name);
    scanf("%s", emp.id);
    scanf("%d", &emp.empNum);
    scanf("%lf", &emp.salary);
    
    printf("%s\n", emp.name);
    printf("%s\n", emp.id);
    printf("%d\n", emp.empNum);
    printf("%.2f\n", emp.salary);
    
    return 0;
}