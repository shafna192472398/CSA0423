#include <stdio.h>
#include <pthread.h>
#include <windows.h>

int counter = 0;
pthread_mutex_t lock;

void* run(void* arg) {
    int id = *(int*)arg;
    int i;

    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        printf("Thread %d updated counter to %d\n", id, counter);
        pthread_mutex_unlock(&lock);
        Sleep(1000);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, run, &id1);
    pthread_create(&t2, NULL, run, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}

