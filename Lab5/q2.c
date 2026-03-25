#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    char name[3];
    int burst;
    int remaining;
    int queue_level; 
    int waiting;
    int turnaround;
} Process;

int main() {
    int n, i, j, time = 0;
    int quanta[3] = {2, 4, 8}; 

    printf("Enter number of processes (max 10): ");
    scanf("%d", &n);

    Process p[MAX];

    for(i=0;i<n;i++) {
        printf("Enter process name and burst time: ");
        scanf("%s %d", p[i].name, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].queue_level = 0;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    int done = 0;
    printf("\nGantt Chart: ");
    while(done < n) {
        done = 0;
        for(i=0;i<n;i++) {
            if(p[i].remaining > 0) {
                int q = p[i].queue_level;
                int t = (p[i].remaining < quanta[q]) ? p[i].remaining : quanta[q];
                printf("|%s ", p[i].name);
                p[i].remaining -= t;
                time += t;
                if(p[i].remaining == 0) {
                    p[i].turnaround = time;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                } else if(p[i].queue_level < 2) {
                    p[i].queue_level++; 
                }
            } else {
                done++;
            }
        }
    }
    printf("|\n");

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    for(i=0;i<n;i++)
        printf("%s\t%d\t%d\t%d\n", p[i].name, p[i].burst, p[i].waiting, p[i].turnaround);

    return 0;
}
