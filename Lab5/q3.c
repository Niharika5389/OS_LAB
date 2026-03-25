#include <stdio.h>

#define MAX 10

typedef struct {
    char name[3];
    int burst;
    int deadline;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n, i, j, time = 0;
    printf("Enter number of processes (max 10): ");
    scanf("%d", &n);

    Process p[MAX], temp;

    for(i=0;i<n;i++) {
        printf("Enter process name, burst time, deadline: ");
        scanf("%s %d %d", p[i].name, &p[i].burst, &p[i].deadline);
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }


    for(i=0;i<n-1;i++) {
        for(j=i+1;j<n;j++) {
            if(p[i].deadline > p[j].deadline) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\nGantt Chart: ");
    for(i=0;i<n;i++) {
        printf("|%s ", p[i].name);
        p[i].waiting = time;
        time += p[i].burst;
        p[i].turnaround = time;
    }
    printf("|\n");

    printf("\nProcess\tBurst\tDeadline\tWaiting\tTurnaround\n");
    for(i=0;i<n;i++)
        printf("%s\t%d\t%d\t\t%d\t%d\n", p[i].name, p[i].burst, p[i].deadline, p[i].waiting, p[i].turnaround);

    return 0;
}
