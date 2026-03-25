#include <stdio.h>

#define SEGMENTS 5

struct Segment {
    int base;
    int limit;
};

int getPhysicalAddress(struct Segment segTable[], int seg, int offset) {
    if (seg >= SEGMENTS) {
        printf("Invalid Segment Number!\n");
        return -1;
    }

    if (offset >= segTable[seg].limit) {
        printf("Addressing Error: Offset exceeds limit!\n");
        return -1;
    }

    return segTable[seg].base + offset;
}

int main() {
    struct Segment segTable[SEGMENTS] = {
        {219, 600},
        {2300, 14},
        {90, 100},
        {1327, 580},
        {1952, 96}
    };

    int seg, offset, physical;

    int testSeg[] = {2, 3, 0};
    int testOffset[] = {53, 852, 1222};

    for (int i = 0; i < 3; i++) {
        seg = testSeg[i];
        offset = testOffset[i];

        printf("\nLogical Address: Segment %d, Offset %d\n", seg, offset);

        physical = getPhysicalAddress(segTable, seg, offset);

        if (physical != -1)
            printf("Physical Address: %d\n", physical);
    }

    return 0;
}