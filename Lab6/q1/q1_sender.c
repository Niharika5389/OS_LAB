#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st {
    long int my_msg_type;
    int number;
};

int main() {
    struct my_msg_st some_data;
    int msgid;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter a number: ");
    scanf("%d", &some_data.number);

    some_data.my_msg_type = 1;

    if (msgsnd(msgid, (void *)&some_data, sizeof(int), 0) == -1) {
        fprintf(stderr, "msgsnd failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
