#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readCount = 0;
int data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %d reads data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);
        readCount--;
        if (readCount == 0)
            sem_post(&wrt);
        sem_post(&mutex);

        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&wrt);
        data++;
        printf("Writer %d writes data = %d\n", id, data);
        sem_post(&wrt);

        sleep(2);
    }
}

int main() {
    pthread_t r1, r2, r3, w1;
    int a=1, b=2, c=3, d=1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&r1, NULL, reader, &a);
    pthread_create(&r2, NULL, reader, &b);
    pthread_create(&r3, NULL, reader, &c);
    pthread_create(&w1, NULL, writer, &d);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
