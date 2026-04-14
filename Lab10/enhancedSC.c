#include <stdio.h>
#include <stdlib.h>

int findPage(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

// find victim based on (R,M) priority: (0,0) > (0,1) > (1,0) > (1,1)
int findVictim(int frames[], int ref[], int modified[], int f, int *pointer) {
    // up to 2 full passes to guarantee finding (0,0) or (0,1)
    for (int pass = 0; pass < 4; pass++) {
        for (int count = 0; count < f; count++) {
            int p = *pointer;
            // pass 0: look for (0,0)
            // pass 1: look for (0,1), clear R bits
            // pass 2: look for (0,0) again after clearing
            // pass 3: look for (0,1) again
            if (pass == 0 && ref[p] == 0 && modified[p] == 0) {
                *pointer = (p + 1) % f;
                return p;
            }
            if (pass == 1 && ref[p] == 0 && modified[p] == 1) {
                *pointer = (p + 1) % f;
                return p;
            }
            if (pass == 1) ref[p] = 0;   // clear R on second pass scan
            if (pass == 2 && ref[p] == 0 && modified[p] == 0) {
                *pointer = (p + 1) % f;
                return p;
            }
            if (pass == 3 && ref[p] == 0 && modified[p] == 1) {
                *pointer = (p + 1) % f;
                return p;
            }
            *pointer = (p + 1) % f;
        }
    }
    // fallback (should never reach here)
    int victim = *pointer;
    *pointer = (*pointer + 1) % f;
    return victim;
}

void EnhancedSecondChance(int pages[], int modified_in[], int n, int f) {
    int *frames   = (int *)malloc(f * sizeof(int));
    int *ref      = (int *)malloc(f * sizeof(int));
    int *modified = (int *)malloc(f * sizeof(int));
    int **table   = (int **)malloc(f * sizeof(int *));
    char *status  = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < f; i++) {
        frames[i]   = -1;
        ref[i]      = 0;
        modified[i] = 0;
        table[i]    = (int *)malloc(n * sizeof(int));
    }

    int faults = 0, hits = 0, pointer = 0;

    for (int i = 0; i < n; i++) {
        int pos = findPage(frames, f, pages[i]);

        if (pos != -1) {
            ref[pos]      = 1;
            modified[pos] = modified_in[i];  // update M bit on hit too
            status[i] = 'H';
            hits++;
        } else {
            int empty = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { empty = j; break; }
            }

            if (empty != -1) {
                frames[empty]   = pages[i];
                ref[empty]      = 1;
                modified[empty] = modified_in[i];
            } else {
                int victim = findVictim(frames, ref, modified, f, &pointer);
                frames[victim]   = pages[i];
                ref[victim]      = 1;
                modified[victim] = modified_in[i];
            }
            status[i] = 'F';
            faults++;
        }

        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }

    printf("\nEnhanced Second Chance Algorithm:\n");
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
    free(modified);
    free(status);
}

int main() {
    int n, f;
    printf("Enter total number of page references: ");
    scanf("%d", &n);
    int *pages      = (int *)malloc(n * sizeof(int));
    int *modified   = (int *)malloc(n * sizeof(int));
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter modified bit for each reference (0 or 1):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &modified[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    EnhancedSecondChance(pages, modified, n, f);

    free(pages);
    free(modified);
    return 0;
}
