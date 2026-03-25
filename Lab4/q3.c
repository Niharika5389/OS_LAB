#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        printf("Child process exiting...\n");
        exit(0);
    }
    else {
        // Parent process
        printf("Parent process sleeping...\n");
        sleep(30);  
        printf("Parent exiting...\n");
    }

    return 0;
}
