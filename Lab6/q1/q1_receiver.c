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

int isPalindrome(int num) {
    int original = num, reverse = 0, rem;
    while (num != 0) {
        rem = num % 10;
        reverse = reverse * 10 + rem;
        num /= 10;
    }
    return original == reverse;
}

int main() {
    int msgid;
    struct my_msg_st some_data;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed\n");
        exit(EXIT_FAILURE);
    }

    if (msgrcv(msgid, (void *)&some_data, sizeof(int), 0, 0) == -1) {
        fprintf(stderr, "msgrcv failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Received number: %d\n", some_data.number);

    if (isPalindrome(some_data.number))
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");

    msgctl(msgid, IPC_RMID, 0);

    exit(EXIT_SUCCESS);
}
