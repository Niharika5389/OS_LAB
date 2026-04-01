#include <stdio.h>
#include <stdlib.h>
 
#define BITS 8  

int findPage(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int findLRU(unsigned char ref[], int f) {
    int min = ref[0], pos = 0;
    for (int i = 1; i < f; i++) {
        if (ref[i] < min) {
            min = ref[i];
            pos = i;
        }
    }
    return pos;
}

void LRU_Aging(int pages[], int n, int f) {
    int *frames = (int *)malloc(f * sizeof(int));
    unsigned char *ref = (unsigned char *)malloc(f * sizeof(unsigned char));

    int **table = (int **)malloc(f * sizeof(int *));
    char *status = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        ref[i] = 0;
        table[i] = (int *)malloc(n * sizeof(int));
    }

    int faults = 0, hits = 0;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < f; j++) {
            ref[j] = ref[j] >> 1;
        }

        int pos = findPage(frames, f, pages[i]);

        if (pos != -1) {
            ref[pos] |= (1 << (BITS - 1)); 
            status[i] = 'H';
            hits++;
        } else {
            int empty = -1;

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                frames[empty] = pages[i];
                ref[empty] = (1 << (BITS - 1));
            } else {
                int lru = findLRU(ref, f);
                frames[lru] = pages[i];
                ref[lru] = (1 << (BITS - 1));
            }

            status[i] = 'F';
            faults++;
        }

        for (int j = 0; j < f; j++) {
            table[j][i] = frames[j];
        }
    }

    printf("\nLRU (Aging Algorithm):\n");

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

    LRU_Aging(pages, n, f);

    free(pages);

    return 0;
}