#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com.h"

int main()
{
    void *shared_memory = NULL;
    struct shared_use_st *shared_stuff;
    int shmid;

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

    while (shared_stuff->written_by_you == 0)
        usleep(10000);

    char ch = shared_stuff->alphabet;

    if ((ch >= 'a' && ch < 'z') || (ch >= 'A' && ch < 'Z'))
        ch++;

    shared_stuff->alphabet = ch;
    shared_stuff->written_by_you = 0;

    shmdt(shared_memory);

    return 0;
}
