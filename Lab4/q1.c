#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int status; pid_t pid;
    pid = fork();

    if(pid == -1){
        printf("\nERROR child not created");
        exit(1);
    }
    else if (pid == 0){
        printf("\nI'm the child!\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());
        exit(0);
    }
    else{
        printf("\nI'm the parent!\n");
        printf("Parent PID : %d\n", getpid());
        wait(&status);
        printf("\n Child complete");
    }

    return 0;
}