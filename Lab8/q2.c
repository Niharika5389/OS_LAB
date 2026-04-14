#include <stdio.h>
#include <stdbool.h>

#define MAXP 20
#define MAXR 3

bool detectDeadlock(int n, int allocation[MAXP][MAXR], int request[MAXP][MAXR], int available[MAXR]) {
    int work[MAXR], count = 0;
    bool finish[MAXP] = {false};

    for(int j = 0; j < MAXR; j++)
        work[j] = available[j];

    while(count < n) {
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;

                for(j = 0; j < MAXR; j++)
                    if(request[i][j] > work[j])
                        break;

                if(j == MAXR) {
                    for(int k = 0; k < MAXR; k++)
                        work[k] += allocation[i][k];

                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if(!found)
            break;  
    }

    bool deadlock = false;
    printf("\nDeadlocked processes: ");

    for(int i = 0; i < n; i++) {
        if(!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if(!deadlock)
        printf("None");

    printf("\n");

    return deadlock;
}

int main() {
    int n;
    int allocation[MAXP][MAXR], request[MAXP][MAXR], available[MAXR];
    int total[MAXR] = {10, 5, 7};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < MAXR; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < MAXR; j++)
            scanf("%d", &request[i][j]);

    for(int j = 0; j < MAXR; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++)
            sum += allocation[i][j];
        available[j] = total[j] - sum;
    }

    printf("\nRunning Deadlock Detection...\n");

    if(detectDeadlock(n, allocation, request, available))
        printf("System is in DEADLOCK.\n");
    else
        printf("System is NOT in deadlock.\n");

    return 0;
}
/*
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
*/

/*
0 0 0
2 0 2
0 0 0
1 0 0 
0 0 2
*/
