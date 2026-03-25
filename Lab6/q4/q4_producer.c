#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com.h"

int main()
{
    void *shared_memory = NULL;
    struct shared_use_st *shared_stuff;
    int shmid;
    char buffer[TEXT_SZ];

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }


    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    shared_stuff = (struct shared_use_st *)shared_memory;

    while (1) {
        while (shared_stuff->written_by_you == 1) {
            printf("Producer waiting for consumer...\n");
            sleep(1);
        }

        printf("Enter a word (or 'end' to quit): ");
        fgets(buffer, TEXT_SZ, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; 

        strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
        shared_stuff->written_by_you = 1;

        if (strcmp(buffer, "end") == 0)
            break;
    }

    if (shmdt(shared_memory) == -1)
        perror("shmdt");

    return 0;
}
