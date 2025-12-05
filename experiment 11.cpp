#include <stdio.h>
#include <windows.h>

int counter = 0;
HANDLE lock;

DWORD WINAPI worker(void *arg) {
    int *data = (int*)arg;
    int id = data[0];
    int inc = data[1];
    for (int i = 0; i < inc; i++) {
        WaitForSingleObject(lock, INFINITE);
        counter++;
        printf("Thread %d incremented counter to %d\n", id, counter);
        ReleaseMutex(lock);
    }
    return 0;
}

int main() {
    int nthreads, inc_per_thread;
    scanf("%d %d", &nthreads, &inc_per_thread);

    HANDLE threads[nthreads];
    int args[nthreads][2];

    lock = CreateMutex(NULL, FALSE, NULL);

    for (int i = 0; i < nthreads; i++) {
        args[i][0] = i + 1;
        args[i][1] = inc_per_thread;
        threads[i] = CreateThread(NULL, 0, worker, args[i], 0, NULL);
    }

    WaitForMultipleObjects(nthreads, threads, TRUE, INFINITE);
    CloseHandle(lock);

    printf("Final counter value: %d\n", counter);
    return 0;
}
