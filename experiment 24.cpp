#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[100];

    // 1. Create or open a file
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        printf("Error opening file!\n");
        return 1;
    }
    printf("File opened successfully!\n");

    // 2. Write to file
    char data[] = "This is a demo of UNIX system calls in C.\n";
    write(fd, data, sizeof(data));
    printf("Data written to file.\n");

    // 3. Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read from file
    int bytesRead = read(fd, buffer, sizeof(buffer));
    buffer[bytesRead] = '\0';
    printf("\nData read from file:\n%s", buffer);

    // 5. Close file
    close(fd);
    printf("\nFile closed successfully.\n");

    return 0;
}
