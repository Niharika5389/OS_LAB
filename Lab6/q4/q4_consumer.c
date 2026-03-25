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


    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666);
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
        while (shared_stuff->written_by_you == 0) {
            usleep(50000); 
        }

        printf("Consumer read: %s\n", shared_stuff->some_text);

        if (strcmp(shared_stuff->some_text, "end") == 0)
            break;

        shared_stuff->written_by_you = 0; 
    }

    if (shmdt(shared_memory) == -1)
        perror("shmdt");

    if (shmctl(shmid, IPC_RMID, 0) == -1)
        perror("shmctl");

    return 0;
}
