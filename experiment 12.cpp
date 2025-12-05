#include <stdio.h>
#include <windows.h>
#include <stdint.h>

#define N 5

HANDLE chopstick[N];

DWORD WINAPI philosopher(LPVOID arg) {
    int id = (int)(intptr_t)arg;
    int left = id;
    int right = (id + 1) % N;

    for (int i = 0; i < 5; i++) {
        Sleep(200);
        WaitForSingleObject(chopstick[left], INFINITE);
        WaitForSingleObject(chopstick[right], INFINITE);

        printf("Philosopher %d is eating\n", id);
        Sleep(200);

        ReleaseMutex(chopstick[left]);
        ReleaseMutex(chopstick[right]);

        printf("Philosopher %d is thinking\n", id);
    }
    return 0;
}

int main() {
    HANDLE threads[N];

    for (int i = 0; i < N; i++)
        chopstick[i] = CreateMutex(NULL, FALSE, NULL);

    for (int i = 0; i < N; i++)
        threads[i] = CreateThread(NULL, 0, philosopher, (LPVOID)(intptr_t)i, 0, NULL);

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);
    return 0;
}
