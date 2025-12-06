#include <stdio.h>

int main() {
    int blockCount, processCount;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blockCount);

    int blockSize[blockCount], blockAllocated[blockCount];

    printf("Enter sizes of each memory block:\n");
    for (int i = 0; i < blockCount; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
        blockAllocated[i] = 0;   // initially free
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &processCount);

    int processSize[processCount], allocation[processCount];

    printf("Enter sizes of each process:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1;  // Initially not allocated
    }

    // First Fit Allocation
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < blockCount; j++) {
            if (blockAllocated[j] == 0 && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockAllocated[j] = 1;  // mark block as allocated
                break;
            }
        }
    }

    // Output
    printf("\n--- First Fit Memory Allocation Result ---\n");
    printf("Process\tSize\tBlock Allocated\n");
    for (int i = 0; i < processCount; i++) {
        printf("P%d\t%d\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
