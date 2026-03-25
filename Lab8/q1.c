#include <stdio.h>
#include <stdbool.h>

#define MAXP 20
#define MAXR 3

bool isSafe(int n, int allocation[MAXP][MAXR], int need[MAXP][MAXR], int available[MAXR]) {
    int work[MAXR], safeSeq[MAXP], count = 0;
    bool finish[MAXP] = {false};

    for(int j = 0; j < MAXR; j++)
        work[j] = available[j];

    while(count < n) {
        bool found = false;
        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < MAXR; j++)
                    if(need[i][j] > work[j])
                        break;
                if(j == MAXR) {
                    for(int k = 0; k < MAXR; k++)
                        work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if(!found)
            return false;
    }

    printf("\nSafe Sequence: ");
    for(int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

bool requestResources(int n, int allocation[MAXP][MAXR], int need[MAXP][MAXR], int available[MAXR]) {
    int process, request[MAXR];

    printf("\nEnter process number: ");
    scanf("%d", &process);
    printf("Enter request (A B C): ");
    for(int j = 0; j < MAXR; j++)
        scanf("%d", &request[j]);

    for(int j = 0; j < MAXR; j++)
        if(request[j] > need[process][j]) {
            printf("Error: Exceeded maximum claim.\n");
            return false;
        }

    for(int j = 0; j < MAXR; j++)
        if(request[j] > available[j]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }

    for(int j = 0; j < MAXR; j++) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }

    if(isSafe(n, allocation, need, available)) {
        printf("Request granted.\n");
        return true;
    } else {
        for(int j = 0; j < MAXR; j++) {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }
        printf("Request denied (Unsafe state).\n");
        return false;
    }
}

int main() {
    int n, total[MAXR] = {10, 5, 7};
    int allocation[MAXP][MAXR], max[MAXP][MAXR], need[MAXP][MAXR], available[MAXR];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < MAXR; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < MAXR; j++)
            scanf("%d", &max[i][j]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < MAXR; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    for(int j = 0; j < MAXR; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++)
            sum += allocation[i][j];
        available[j] = total[j] - sum;
    }
    printf("\nNeed matrix:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < MAXR; j++){
            printf("%d ",need[i][j]);
        }printf("\n");
    }

    printf("\nInitial Safety Check:\n");
    if(isSafe(n, allocation, need, available))
        printf("System is initially SAFE.\n");
    else {
        printf("System is NOT SAFE.\n");
        return 0;
    }
    int c=1;
    while(c!=0){
        printf("Resourse-request ? (y=1/n=0)");
        scanf("%d",&c);
        if(c==1){
            requestResources(n, allocation, need, available);
        }
    }
    

    return 0;
}

/*
Enter Allocation Matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Enter Max Matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
*/