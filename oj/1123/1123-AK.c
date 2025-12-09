#include <stdio.h>
#include <string.h>

struct Employee {
    char name[50];
    char id[20];
    int age;
    double salary;
};

int main() {
    struct Employee employees[5];
    double maxSalary = 0.0;
    
    for (int i = 0; i < 5; i++) 
    {
        scanf("%s", employees[i].name);
        scanf("%s", employees[i].id);
        scanf("%d", &employees[i].age);
        scanf("%lf", &employees[i].salary);
        
        if (employees[i].salary > maxSalary) 
        {
            maxSalary = employees[i].salary;
        }
    }
    
    printf("%.2f\n", maxSalary);
    
    return 0;
}