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

// LOOK
void LOOK(int req[], int n, int head) {
    int total = 0;
    sort(req, n);

    for (int i = n - 1; i >= 0; i--) {
        if (req[i] < head) {
            total += absDiff(head, req[i]);
            head = req[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (req[i] > head) {
            total += absDiff(head, req[i]);
            head = req[i];
        }
    }

    printf("LOOK Total Head Movement = %d\n", total);
}

void CLOOK(int req[], int n, int head) {
    int total = 0;
    sort(req, n);

    int i;
    int pos = 0;

    while (pos < n && req[pos] < head)
        pos++;

    for (i = pos; i < n; i++) {
        total += absDiff(head, req[i]);
        head = req[i];
    }

    if (pos > 0)
        head = req[0];

    for (i = 1; i < pos; i++) {
        total += absDiff(head, req[i]);
        head = req[i];
    }

    printf("C-LOOK Total Head Movement = %d\n", total);
}

int main() {
    int n, head;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[100];
    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    LOOK(req, n, head);
    CLOOK(req, n, head);

    return 0;
}