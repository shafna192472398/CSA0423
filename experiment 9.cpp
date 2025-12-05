#include <stdio.h>
#include <string.h>

int main() {
    char shared_memory[100];
    char parent_msg[100];
    
    printf("Parent writes: ");
    gets(parent_msg);
    
    strcpy(shared_memory, parent_msg);
    
    printf("Child reads: %s\n", shared_memory);
    
    return 0;
}
