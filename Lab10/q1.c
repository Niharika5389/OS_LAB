#include <stdio.h>
#include <stdlib.h>

int isPresent(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

void FIFO(int pages[], int n, int f) {
    int *frames = (int *)malloc(f * sizeof(int));
    int **table = (int **)malloc(f * sizeof(int *));
    char *status = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        table[i] = (int *)malloc(n * sizeof(int));
    }

    int index = 0, faults = 0;

    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, f, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
            status[i] = 'F';
        } else {
            status[i] = 'H';
        }

        // store snapshot
        for (int j = 0; j < f; j++) {
            table[j][i] = frames[j];
        }
    }

    printf("\nFIFO Page Replacement:\n");

    printf("Pages:   ");
    for (int i = 0; i < n; i++)
        printf("%2d ", pages[i]);

    printf("\n");

    for (int i = 0; i < f; i++) {
        printf("Frame %d: ", i);
        for (int j = 0; j < n; j++) {
            if (table[i][j] == -1)
                printf(" - ");
            else
                printf("%2d ", table[i][j]);
        }
        printf("\n");
    }

    printf("Status:  ");
    for (int i = 0; i < n; i++)
        printf(" %c ", status[i]);

    printf("\nTotal FIFO Page Faults: %d\n", faults);

    for (int i = 0; i < f; i++)
        free(table[i]);
    free(table);
    free(frames);
    free(status);
}

int findOptimal(int pages[], int frames[], int n, int f, int current) {
    int farthest = current, index = -1;

    for (int i = 0; i < f; i++) {
        int j;
        for (j = current + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }

    return (index == -1) ? 0 : index;
}

void OPTIMAL(int pages[], int n, int f) {
    int *frames = (int *)malloc(f * sizeof(int));
    int **table = (int **)malloc(f * sizeof(int *));
    char *status = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        table[i] = (int *)malloc(n * sizeof(int));
    }

    int faults = 0;

    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, f, pages[i])) {
            int j;
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    faults++;
                    break;
                }
            }

            if (j == f) {
                int pos = findOptimal(pages, frames, n, f, i);
                frames[pos] = pages[i];
                faults++;
            }

            status[i] = 'F';
        } else {
            status[i] = 'H';
        }

        // store snapshot
        for (int j = 0; j < f; j++) {
            table[j][i] = frames[j];
        }
    }

    printf("\nOptimal Page Replacement:\n");

    printf("Pages:   ");
    for (int i = 0; i < n; i++)
        printf("%2d ", pages[i]);

    printf("\n");

    for (int i = 0; i < f; i++) {
        printf("Frame %d: ", i);
        for (int j = 0; j < n; j++) {
            if (table[i][j] == -1)
                printf(" - ");
            else
                printf("%2d ", table[i][j]);
        }
        printf("\n");
    }

    printf("Status:  ");
    for (int i = 0; i < n; i++)
        printf(" %c ", status[i]);

    printf("\nTotal Optimal Page Faults: %d\n", faults);

    // free memory
    for (int i = 0; i < f; i++)
        free(table[i]);
    free(table);
    free(frames);
    free(status);
}

int main() {
    int n, f;

    printf("Enter total number of page references: ");
    scanf("%d", &n);

    int *pages = (int *)malloc(n * sizeof(int));

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    FIFO(pages, n, f);
    OPTIMAL(pages, n, f);

    free(pages);

    return 0;
}