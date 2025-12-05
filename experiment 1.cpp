#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent Process:\n");
    printf("PID = %lu\n", GetCurrentProcessId());

    if (CreateProcess(
            NULL,
            "notepad.exe",
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi
        )) {

        printf("Child Process Created:\n");
        printf("PID = %lu\n", pi.dwProcessId);
        printf("Parent PID = %lu\n", GetCurrentProcessId());

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Process creation failed\n");
    }

    return 0;
}
