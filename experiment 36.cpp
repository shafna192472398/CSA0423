#include <stdio.h>

struct Block {
    int data;
    int next;
};

int main() {
    int n, i;
    struct Block file[50];
    int start, end;

    printf("Enter number of blocks in file: ");
    scanf("%d", &n);

    printf("Enter starting block number: ");
    scanf("%d", &start);

    printf("Enter ending block number: ");
    scanf("%d", &end);

    printf("\nEnter block numbers (in order):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &file[i].data);
        if (i == n - 1)
            file[i].next = -1;  // last block
        else
            file[i].next = file[i + 1].data;
    }

    printf("\nLinked File Allocation:\n");
    printf("Start Block = %d\n", start);
    printf("End Block   = %d\n\n", end);

    printf("Block ? Next\n");
    for (i = 0; i < n; i++)
        printf("%d ? %d\n", file[i].data, file[i].next);

    return 0;
}
