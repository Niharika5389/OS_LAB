#include <stdio.h>

#define BLOCKS 5
#define PROCESSES 4

void firstFit(int blockSize[], int processSize[]) {
    int allocation[PROCESSES];
    
    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < BLOCKS; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] != -1)
            printf("Process %d (%dK) -> Block %d\n", i+1, processSize[i], allocation[i]+1);
        else
            printf("Process %d (%dK) -> Not Allocated\n", i+1, processSize[i]);
    }
}

void bestFit(int blockSize[], int processSize[]) {
    int allocation[PROCESSES];

    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    for (int i = 0; i < PROCESSES; i++) {
        int bestIdx = -1;
        for (int j = 0; j < BLOCKS; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] != -1)
            printf("Process %d (%dK) -> Block %d\n", i+1, processSize[i], allocation[i]+1);
        else
            printf("Process %d (%dK) -> Not Allocated\n", i+1, processSize[i]);
    }
}

void worstFit(int blockSize[], int processSize[]) {
    int allocation[PROCESSES];

    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    for (int i = 0; i < PROCESSES; i++) {
        int worstIdx = -1;
        for (int j = 0; j < BLOCKS; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < PROCESSES; i++) {
        if (allocation[i] != -1)
            printf("Process %d (%dK) -> Block %d\n", i+1, processSize[i], allocation[i]+1);
        else
            printf("Process %d (%dK) -> Not Allocated\n", i+1, processSize[i]);
    }
}

int main() {
    int blocks[BLOCKS] = {100, 500, 200, 300, 600};
    int processes[PROCESSES] = {212, 417, 112, 426};

    int blocks1[BLOCKS], blocks2[BLOCKS], blocks3[BLOCKS];

    for (int i = 0; i < BLOCKS; i++) {
        blocks1[i] = blocks[i];
        blocks2[i] = blocks[i];
        blocks3[i] = blocks[i];
    }

    firstFit(blocks1, processes);
    bestFit(blocks2, processes);
    worstFit(blocks3, processes);

    return 0;
}