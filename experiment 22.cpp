#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {
    FILE *fp;
    struct Employee e;
    int choice, recno;

    while (1) {
        printf("\n1. Add Employee\n2. Display All\n3. Search by Record Number\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            fp = fopen("employee.dat", "ab+");
            if (!fp) {
                printf("File error");
                return 0;
            }
            printf("Enter ID: ");
            scanf("%d", &e.id);
            printf("Enter Name: ");
            scanf("%s", e.name);
            printf("Enter Salary: ");
            scanf("%f", &e.salary);
            fseek(fp, 0, SEEK_END);
            fwrite(&e, sizeof(e), 1, fp);
            fclose(fp);
        }

        else if (choice == 2) {
            fp = fopen("employee.dat", "rb");
            if (!fp) {
                printf("File not found");
                continue;
            }
            while (fread(&e, sizeof(e), 1, fp)) {
                printf("\nID: %d", e.id);
                printf("\nName: %s", e.name);
                printf("\nSalary: %.2f\n", e.salary);
            }
            fclose(fp);
        }

        else if (choice == 3) {
            fp = fopen("employee.dat", "rb");
            if (!fp) {
                printf("File not found");
                continue;
            }
            printf("Enter Record Number: ");
            scanf("%d", &recno);
            fseek(fp, (recno - 1) * sizeof(e), SEEK_SET);
            if (fread(&e, sizeof(e), 1, fp)) {
                printf("\nID: %d", e.id);
                printf("\nName: %s", e.name);
                printf("\nSalary: %.2f\n", e.salary);
            } else {
                printf("Record not found\n");
            }
            fclose(fp);
        }

        else if (choice == 4) {
            break;
        }
    }

    return 0;
}
