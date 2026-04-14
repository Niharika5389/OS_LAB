#include <stdio.h>
#include <stdlib.h>

int findPage(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

// returns index of frame with smallest count
int findLFU(int count[], int f) {
    int min = count[0], pos = 0;
    for (int i = 1; i < f; i++) {
        if (count[i] < min) {
            min = count[i];
            pos = i;
        }
    }
    return pos;
}

// returns index of frame with largest count
int findMFU(int count[], int f) {
    int max = count[0], pos = 0;
    for (int i = 1; i < f; i++) {
        if (count[i] > max) {
            max = count[i];
            pos = i;
        }
    }
    return pos;
}

void LFU(int pages[], int n, int f) {
    int *frames = (int *)malloc(f * sizeof(int));
    int *count  = (int *)malloc(f * sizeof(int));
    int **table = (int **)malloc(f * sizeof(int *));
    char *status = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        count[i]  = 0;
        table[i]  = (int *)malloc(n * sizeof(int));
    }

    int faults = 0, hits = 0;

    for (int i = 0; i < n; i++) {
        int pos = findPage(frames, f, pages[i]);

        if (pos != -1) {
            count[pos]++;
            status[i] = 'H';
            hits++;
        } else {
            int empty = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { 
                  empty = j; 
                  break; }
            }

            if (empty != -1) {
                frames[empty] = pages[i];
                count[empty]  = 1;
            } else {
                int lfu = findLFU(count, f);
                frames[lfu] = pages[i];
                count[lfu]  = 1;
            }
            status[i] = 'F';
            faults++;
        }

        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }

    printf("\nLFU Algorithm:\n");
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

    float hit_ratio = (float)hits / n;
    printf("\nTotal Page Faults: %d\n", faults);
    printf("Hit Ratio: %.2f\n", hit_ratio);

    for (int i = 0; i < f; i++)
        free(table[i]);
    free(table);
    free(frames);
    free(count);
    free(status);
}

void MFU(int pages[], int n, int f) {
    int *frames = (int *)malloc(f * sizeof(int));
    int *count  = (int *)malloc(f * sizeof(int));
    int **table = (int **)malloc(f * sizeof(int *));
    char *status = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        count[i]  = 0;
        table[i]  = (int *)malloc(n * sizeof(int));
    }

    int faults = 0, hits = 0;

    for (int i = 0; i < n; i++) {
        int pos = findPage(frames, f, pages[i]);

        if (pos != -1) {
            count[pos]++;
            status[i] = 'H';
            hits++;
        } else {
            int empty = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { 
                  empty = j; 
                  break; }
            }

            if (empty != -1) {
                frames[empty] = pages[i];
                count[empty]  = 1;
            } else {
                int mfu = findMFU(count, f);
                frames[mfu] = pages[i];
                count[mfu]  = 1;
            }
            status[i] = 'F';
            faults++;
        }

        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }

    printf("\nMFU Algorithm:\n");
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

    float hit_ratio = (float)hits / n;
    printf("\nTotal Page Faults: %d\n", faults);
    printf("Hit Ratio: %.2f\n", hit_ratio);

    for (int i = 0; i < f; i++)
        free(table[i]);
    free(table);
    free(frames);
    free(count);
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

    LFU(pages, n, f);
    MFU(pages, n, f);

    free(pages);
    return 0;
}
