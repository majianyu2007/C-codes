#include <stdio.h>

void scheduler(int task[], int n, int system_task[], int user_task[]) {
    int sys_count = 0;
    int user_count = 0;
    
    // First pass: collect valid tasks into their respective arrays
    int sys_priorities[n], sys_indices[n];
    int user_priorities[n], user_indices[n];
    
    for (int i = 0; i < n; i++) {
        if (task[i] < 50) {
            sys_priorities[sys_count] = task[i];
            sys_indices[sys_count] = i;
            sys_count++;
        } else if (task[i] >= 50 && task[i] <= 255) {
            user_priorities[user_count] = task[i];
            user_indices[user_count] = i;
            user_count++;
        }
        // Priority > 255 is invalid, skip
    }
    
    // Sort system tasks by priority (stable sort - bubble sort)
    for (int i = 0; i < sys_count - 1; i++) {
        for (int j = 0; j < sys_count - 1 - i; j++) {
            if (sys_priorities[j] > sys_priorities[j + 1]) {
                int temp = sys_priorities[j];
                sys_priorities[j] = sys_priorities[j + 1];
                sys_priorities[j + 1] = temp;
                
                temp = sys_indices[j];
                sys_indices[j] = sys_indices[j + 1];
                sys_indices[j + 1] = temp;
            }
        }
    }
    
    // Sort user tasks by priority (stable sort - bubble sort)
    for (int i = 0; i < user_count - 1; i++) {
        for (int j = 0; j < user_count - 1 - i; j++) {
            if (user_priorities[j] > user_priorities[j + 1]) {
                int temp = user_priorities[j];
                user_priorities[j] = user_priorities[j + 1];
                user_priorities[j + 1] = temp;
                
                temp = user_indices[j];
                user_indices[j] = user_indices[j + 1];
                user_indices[j + 1] = temp;
            }
        }
    }
    
    // Copy to output arrays
    for (int i = 0; i < sys_count; i++) {
        system_task[i] = sys_indices[i];
    }
    system_task[sys_count] = -1;
    
    for (int i = 0; i < user_count; i++) {
        user_task[i] = user_indices[i];
    }
    user_task[user_count] = -1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int task[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &task[i]);
    }
    
    int system_task[n + 1];
    int user_task[n + 1];
    
    scheduler(task, n, system_task, user_task);
    
    // Print system tasks
    for (int i = 0; system_task[i] != -1; i++) {
        if (i > 0) printf(" ");
        printf("%d", system_task[i]);
    }
    printf(" -1\n");
    
    // Print user tasks
    for (int i = 0; user_task[i] != -1; i++) {
        if (i > 0) printf(" ");
        printf("%d", user_task[i]);
    }
    printf(" -1\n");
    
    return 0;
}