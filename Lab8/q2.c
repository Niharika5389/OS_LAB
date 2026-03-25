#include <stdio.h>
#include <stdbool.h>

#define MAXP 20
#define MAXR 3

bool isSafe(int n, int allocation[MAXP][MAXR], int need[MAXP][MAXR], int available[MAXR]) {
    int work[MAXR], count = 0;
    bool finish[MAXP] = {false};

    for (int j = 0; j < MAXR; j++)
        work[j] = available[j];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAXR; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == MAXR) {
                    for (int k = 0; k < MAXR; k++)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int main() {
    int n, m = MAXR;
    int allocation[MAXP][MAXR], max[MAXP][MAXR], need[MAXP][MAXR], available[MAXR];
    int total_resources[MAXR] = {10, 5, 7};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    for (int j = 0; j < m; j++) {
        int sum_alloc = 0;
        for (int i = 0; i < n; i++)
            sum_alloc += allocation[i][j];
        available[j] = total_resources[j] - sum_alloc;
    }

    if (!isSafe(n, allocation, need, available)) {
        printf("System is NOT initially safe.\n");
        return 0;
    }
    printf("System is initially SAFE.\n");

    int p, request[MAXR];
    printf("Enter process number making request: ");
    scanf("%d", &p);
    printf("Enter request vector (A B C): ");
    for (int j = 0; j < m; j++)
        scanf("%d", &request[j]);

    for (int j = 0; j < m; j++) {
        if (request[j] > need[p][j]) {
            printf("Error: Request exceeds process maximum claim.\n");
            return 0;
        }
    }

    for (int j = 0; j < m; j++) {
        if (request[j] > available[j]) {
            printf("Request cannot be granted immediately. Not enough resources.\n");
            return 0;
        }
    }

    for (int j = 0; j < m; j++) {
        available[j] -= request[j];
        allocation[p][j] += request[j];
        need[p][j] -= request[j];
    }

    if (isSafe(n, allocation, need, available))
        printf("Request granted. System remains SAFE.\n");
    else {
        for (int j = 0; j < m; j++) {
            available[j] += request[j];
            allocation[p][j] -= request[j];
            need[p][j] += request[j];
        }
        printf("Request cannot be granted as system would be UNSAFE.\n");
    }

    return 0;
}

/*
0 0 0 
2 0 2 
0 0 0 
1 0 0 
0 0 2
*/