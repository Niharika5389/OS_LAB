#include <stdio.h>

#define MAX 10

typedef struct {
    char name[3];
    int arrival;
    int burst;
    int priority;
    int remaining;
    int waiting;
    int turnaround;
} Process;

void fcfs(Process p[], int n);
void srtf(Process p[], int n);
void rr(Process p[], int n, int quantum);
void priority_np(Process p[], int n);

int main() {
    Process p[4] = {
        {"P1", 0, 6, 3, 6, 0, 0},
        {"P2", 3, 3, 2, 3, 0, 0},
        {"P3", 4, 4, 1, 4, 0, 0},
        {"P4", 9, 1, 4, 1, 0, 0}
    };
    
    int choice, n = 4;
    int quantum = 10;

    while(1) {
        printf("\nCPU Scheduling Algorithms:\n");
        printf("1. FCFS\n2. SRTF\n3. Round-Robin\n4. Non-preemptive Priority\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs(p, n); break;
            case 2: srtf(p, n); break;
            case 3: rr(p, n, quantum); break;
            case 4: priority_np(p, n); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}

// ---------- FCFS ----------
void fcfs(Process p[], int n) {
    int time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nGantt Chart: ");
    for(int i=0; i<n; i++) {
        if(time < p[i].arrival)
            time = p[i].arrival;
        printf("|%s ", p[i].name);
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }
    printf("|\n");

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i=0; i<n; i++)
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);

    printf("Average waiting time = %.2f\n", total_wt/n);
    printf("Average turnaround time = %.2f\n", total_tat/n);
}

// ---------- SRTF ----------
void srtf(Process p[], int n) {
    int completed = 0, time = 0, min_idx;
    int remaining[n];
    for(int i=0;i<n;i++) remaining[i]=p[i].burst;
    float total_wt = 0, total_tat = 0;

    printf("\nGantt Chart: ");
    while(completed < n) {
        int min = 100000, found = 0;
        for(int i=0;i<n;i++) {
            if(p[i].arrival <= time && remaining[i]>0 && remaining[i]<min) {
                min = remaining[i];
                min_idx = i;
                found = 1;
            }
        }
        if(!found) { time++; continue; }

        printf("|%s ", p[min_idx].name);
        remaining[min_idx]--;
        time++;
        if(remaining[min_idx]==0) {
            completed++;
            p[min_idx].turnaround = time - p[min_idx].arrival;
            p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;
            total_wt += p[min_idx].waiting;
            total_tat += p[min_idx].turnaround;
        }
    }
    printf("|\n");

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i=0;i<n;i++)
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);

    printf("Average waiting time = %.2f\n", total_wt/n);
    printf("Average turnaround time = %.2f\n", total_tat/n);
}

// ---------- Round-Robin ----------
void rr(Process p[], int n, int quantum) {
    int time = 0, done = 0;
    int remaining[n];
    for(int i=0;i<n;i++) remaining[i]=p[i].burst;
    float total_wt=0,total_tat=0;

    printf("\nGantt Chart: ");
    while(done<n) {
        int all_idle = 1;
        for(int i=0;i<n;i++) {
            if(remaining[i]>0 && p[i].arrival<=time) {
                all_idle=0;
                printf("|%s ",p[i].name);
                int t = (remaining[i] > quantum) ? quantum : remaining[i];
                remaining[i]-=t;
                time += t;
                if(remaining[i]==0) {
                    done++;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    total_wt += p[i].waiting;
                    total_tat += p[i].turnaround;
                }
            }
        }
        if(all_idle) time++;
    }
    printf("|\n");

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i=0;i<n;i++)
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);

    printf("Average waiting time = %.2f\n", total_wt/n);
    printf("Average turnaround time = %.2f\n", total_tat/n);
}

// ---------- Non-preemptive Priority ----------
void priority_np(Process p[], int n) {
    int completed = 0, time = 0, done[n];
    for(int i=0;i<n;i++) done[i]=0;
    float total_wt=0, total_tat=0;

    printf("\nGantt Chart: ");
    while(completed<n) {
        int max_priority=-1, idx=-1;
        for(int i=0;i<n;i++) {
            if(p[i].arrival<=time && !done[i]) {
                if(p[i].priority>max_priority) {
                    max_priority=p[i].priority;
                    idx=i;
                }
            }
        }
        if(idx==-1) { time++; continue; }

        printf("|%s ", p[idx].name);
        time += p[idx].burst;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        total_wt += p[idx].waiting;
        total_tat += p[idx].turnaround;
        done[idx] = 1;
        completed++;
    }
    printf("|\n");

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for(int i=0;i<n;i++)
        printf("%s\t%d\t%d\t%d\t\t%d\t%d\n", p[i].name, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turnaround);

    printf("Average waiting time = %.2f\n", total_wt/n);
    printf("Average turnaround time = %.2f\n", total_tat/n);
}
