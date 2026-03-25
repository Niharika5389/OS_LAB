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
        execlp("./q1", "q1", NULL);
        perror("exec failure");
        exit(1);
    }
    else{
        wait(&status);
        printf("\n Child complete");
    }

    return 0;
}