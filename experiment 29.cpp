#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5;   // Buffer size = 5
int x = 0;       // Item number

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer() {
    if (mutex == 1 && empty != 0) {
        mutex = wait(mutex);
        full = signal(full);
        empty = wait(empty);
        x++;
        printf("\nProducer produced item %d", x);
        mutex = signal(mutex);
    } else {
        printf("\nBuffer is full! Producer cannot produce.");
    }
}

void consumer() {
    if (mutex == 1 && full != 0) {
        mutex = wait(mutex);
        full = wait(full);
        empty = signal(empty);
        printf("\nConsumer consumed item %d", x);
        x--;
        mutex = signal(mutex);
    } else {
        printf("\nBuffer is empty! Consumer cannot consume.");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n\n===== PRODUCER - CONSUMER SIMULATION =====");
        printf("\n1. Produce");
        printf("\n2. Consume");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;

            case 2:
                consumer();
                break;

            case 3:
                exit(0);

            default:
                printf("\nInvalid choice!");
        }

        printf("\n\nBuffer Status ? full = %d, empty = %d, items = %d\n",
               full, empty, x);
    }

    return 0;
}
