#include <stdio.h>
#include <string.h>

#define MAX_USERS 20
#define MAX_FILES 20

struct Directory {
    char dname[20];
    char fname[MAX_FILES][20];
    int fcount;
};

int main() {
    struct Directory dir[MAX_USERS];
    int userCount = 0;
    int choice;
    int i, j;
    char uname[20], fname[20];

    while (1) {
        printf("\nTwo Level Directory Structure");
        printf("\n1. Create User Directory");
        printf("\n2. Create File");
        printf("\n3. Delete File");
        printf("\n4. Search File");
        printf("\n5. Display Directory");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            if (userCount == MAX_USERS) {
                printf("Maximum user directories reached\n");
                break;
            }
            printf("Enter user directory name: ");
            scanf("%s", uname);

            for (i = 0; i < userCount; i++) {
                if (strcmp(uname, dir[i].dname) == 0) {
                    printf("User directory already exists\n");
                    goto skip1;
                }
            }

            strcpy(dir[userCount].dname, uname);
            dir[userCount].fcount = 0;
            userCount++;
            printf("User directory created\n");
        skip1:
            break;

        case 2:
            printf("Enter user directory name: ");
            scanf("%s", uname);

            for (i = 0; i < userCount; i++) {
                if (strcmp(uname, dir[i].dname) == 0) {
                    if (dir[i].fcount == MAX_FILES) {
                        printf("File limit reached\n");
                        goto skip2;
                    }
                    printf("Enter file name: ");
                    scanf("%s", fname);

                    for (j = 0; j < dir[i].fcount; j++) {
                        if (strcmp(fname, dir[i].fname[j]) == 0) {
                            printf("File already exists\n");
                            goto skip2;
                        }
                    }

                    strcpy(dir[i].fname[dir[i].fcount], fname);
                    dir[i].fcount++;
                    printf("File created\n");
                    goto skip2;
                }
            }
            printf("User directory not found\n");
        skip2:
            break;

        case 3:
            printf("Enter user directory name: ");
            scanf("%s", uname);

            for (i = 0; i < userCount; i++) {
                if (strcmp(uname, dir[i].dname) == 0) {
                    printf("Enter file name to delete: ");
                    scanf("%s", fname);

                    for (j = 0; j < dir[i].fcount; j++) {
                        if (strcmp(fname, dir[i].fname[j]) == 0) {
                            strcpy(dir[i].fname[j], dir[i].fname[dir[i].fcount - 1]);
                            dir[i].fcount--;
                            printf("File deleted\n");
                            goto skip3;
                        }
                    }
                    printf("File not found\n");
                    goto skip3;
                }
            }
            printf("User directory not found\n");
        skip3:
            break;

        case 4:
            printf("Enter user directory name: ");
            scanf("%s", uname);

            for (i = 0; i < userCount; i++) {
                if (strcmp(uname, dir[i].dname) == 0) {
                    printf("Enter file name to search: ");
                    scanf("%s", fname);

                    for (j = 0; j < dir[i].fcount; j++) {
                        if (strcmp(fname, dir[i].fname[j]) == 0) {
                            printf("File found\n");
                            goto skip4;
                        }
                    }
                    printf("File not found\n");
                    goto skip4;
                }
            }
            printf("User directory not found\n");
        skip4:
            break;

        case 5:
            printf("\nDirectory Contents:\n");
            for (i = 0; i < userCount; i++) {
                printf("\nUser: %s\n", dir[i].dname);
                if (dir[i].fcount == 0)
                    printf("  No files\n");
                else {
                    for (j = 0; j < dir[i].fcount; j++)
                        printf("  %s\n", dir[i].fname[j]);
                }
            }
            break;

        case 6:
            return 0;

        default:
            printf("Invalid choice\n");
        }
    }
}
