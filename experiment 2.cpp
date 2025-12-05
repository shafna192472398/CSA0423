#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buffer[1024];
    int bytes;

    src = open("source.txt", O_RDONLY);
    if (src < 0) {
        printf("Source file error\n");
        return 1;
    }

    dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        printf("Destination file error\n");
        close(src);
        return 1;
    }

    while ((bytes = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytes);
    }

    close(src);
    close(dest);
    printf("File copied successfully\n");

    return 0;
}
