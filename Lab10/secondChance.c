#include <stdio.h>
#include <stdlib.h>

int findPage(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

void SecondChance(int pages[], int n, int f) {
    int *frames = (int *)malloc(f * sizeof(int));
    int *ref    = (int *)malloc(f * sizeof(int));
    int **table = (int **)malloc(f * sizeof(int *));
    char *status = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        ref[i]    = 0;
        table[i]  = (int *)malloc(n * sizeof(int));
    }

    int faults = 0, hits = 0, pointer = 0;

    for (int i = 0; i < n; i++) {
        int pos = findPage(frames, f, pages[i]);

        if (pos != -1) {
            ref[pos] = 1;        // set reference bit on hit
            status[i] = 'H';
            hits++;
        } else {
            // find a victim using clock hand
            while (ref[pointer] == 1) {
                ref[pointer] = 0;       // give second chance
                pointer = (pointer + 1) % f;
            }
            frames[pointer] = pages[i];
            ref[pointer]    = 1;
            pointer = (pointer + 1) % f;
            status[i] = 'F';
            faults++;
        }

        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }

    printf("\nSecond Chance (Clock) Algorithm:\n");
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
    free(ref);
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

    SecondChance(pages, n, f);

    free(pages);
    return 0;
}
