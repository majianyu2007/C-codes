#include <stdio.h>

int days(int year, int month) {
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        } else {
            return 28;
        }
    }
    
    return days_in_month[month];
}

int main() {
    int year, month;
    
    scanf("%d %d", &year, &month);
    
    if (year <= 1000 || year >= 3000) {
        printf("invalid year!\n");
        return 0;
    }
    
    if (month <= 0 || month >= 13) {
        printf("invalid month!\n");
        return 0;
    }
    
    printf("%d\n", days(year, month));
    
    return 0;
}