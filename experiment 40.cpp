#include <stdio.h>

int main() {
    printf("Linux File Access Permissions:\n");
    printf("-----------------------------------\n");
    printf("r = read permission\n");
    printf("w = write permission\n");
    printf("x = execute permission\n");
    printf("\nPermission format: rwx rwx rwx\n");
    printf("                     |   |   |\n");
    printf("                     |   |   +-- others\n");
    printf("                     |   +------ group\n");
    printf("                     +---------- owner/user\n\n");

    printf("Linux User Types:\n");
    printf("-----------------------------------\n");
    printf("1. Owner (u)  – creator of file\n");
    printf("2. Group (g)  – users in same group\n");
    printf("3. Others (o) – everyone else\n");

    printf("\nExamples:\n");
    printf("chmod 755 file → rwx r-x r-x\n");
    printf("chmod 644 file → rw- r-- r--\n");

    return 0;
}
