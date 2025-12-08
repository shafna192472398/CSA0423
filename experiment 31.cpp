#include <stdio.h>

int main() {
    int frames, pages, page[50], frame[10], i, j, k = 0, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string: ");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    for (i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < pages; i++) {
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[k] = page[i];
            k = (k + 1) % frames;
            faults++;
        }

        printf("Page %d -> ", page[i]);
        for (j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
