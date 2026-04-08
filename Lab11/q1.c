#include <stdio.h>
#include <stdlib.h>

int absDiff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

// FCFS
void FCFS(int req[], int n, int head) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += absDiff(head, req[i]);
        head = req[i];
    }
    printf("FCFS Total Head Movement = %d\n", total);
}

// SSTF
void SSTF(int req[], int n, int head) {
    int total = 0, visited[100] = {0};

    for (int i = 0; i < n; i++) {
        int min = 1e9, index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int d = absDiff(head, req[j]);
                if (d < min) {
                    min = d;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += min;
        head = req[index];
    }

    printf("SSTF Total Head Movement = %d\n", total);
}

// SCAN
void SCAN(int req[], int n, int head, int size) {
    int total = 0;
    sort(req, n);

    for (int i = n - 1; i >= 0; i--) {
        if (req[i] <= head) {
            total += absDiff(head, req[i]);
            head = req[i];
        }
    }

    total += absDiff(head, 0);
    head = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] > head) {
            total += absDiff(head, req[i]);
            head = req[i];
        }
    }

    printf("SCAN Total Head Movement = %d\n", total);
}

// C-SCAN
void CSCAN(int req[], int n, int head, int size) {
    int total = 0;
    sort(req, n);

    int i;
    int start = head;

    for (i = 0; i < n; i++) {
        if (req[i] >= head) {
            total += absDiff(head, req[i]);
            head = req[i];
        }
    }

    total += absDiff(head, size - 1);

    head = 0;

    for (i = 0; i < n; i++) {
        if (req[i] < start) { 
            total += absDiff(head, req[i]);
            head = req[i];
        }
    }

    printf("C-SCAN Total Head Movement = %d\n", total);
}

int main() {
    int n, head, size;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[100];
    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    FCFS(req, n, head);
    SSTF(req, n, head);
    SCAN(req, n, head, size);
    CSCAN(req, n, head, size);

    return 0;
}