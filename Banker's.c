#include <stdio.h>
#include <stdbool.h>
#define MAX_RESOURCES 10
#define MAX_PROCESSES 10
int avail_r[MAX_RESOURCES];
int allocated_resources[MAX_PROCESSES][MAX_RESOURCES];
int maximum_resources[MAX_PROCESSES][MAX_RESOURCES];
int need_resources[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];
int np, nr;
int main() {
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter the number of resources: ");
    scanf("%d", &nr);
    printf("Enter the available resources: ");
    for (i = 0; i < nr; i++) {
        scanf("%d", &avail_r[i]);
    }
    printf("Enter the allocation :\n");
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            scanf("%d", &allocated_resources[i][j]);
        }
    }
    printf("Enter the maximum :\n");
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            scanf("%d", &maximum_resources[i][j]);
        }
    }
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            need_resources[i][j] = maximum_resources[i][j] - allocated_resources[i][j];
        }
    }
    int work[MAX_RESOURCES];
    int finish_copy[MAX_PROCESSES];
    int count = 0;
    int safe_sequence[MAX_PROCESSES];
    for (i = 0; i < nr; i++) {
        work[i] = avail_r[i];

    }
    for (i = 0; i < np; i++) {
        finish_copy[i] = finish[i];
    }
    while (count < np) {
        int found = false;
        for (i = 0; i < np; i++) {
            if (!finish_copy[i]) {
                int can_allocate = true;

                for (j = 0; j < nr; j++) {
                    if (need_resources[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (j = 0; j < nr; j++) {
                        work[j] += allocated_resources[i][j];
                    }
                    finish_copy[i] = true;
                    safe_sequence[count] = i;
                    count++;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    if (count == np) {
        printf("Safe Sequence: ");
        for (i = 0; i < np; i++) {
            printf("P%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is in an unsafe state. No safe sequence.\n");
    }
}
