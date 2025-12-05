#include <stdio.h>
#include <string.h>

struct message {
    long type;
    char text[100];
};

int main() {
    struct message mq;
    char input[100];
    
    printf("Child sends: ");
    gets(input);
    
    mq.type = 1;
    strcpy(mq.text, input);
    
    printf("Parent receives: %s\n", mq.text);
    
    return 0;
}
