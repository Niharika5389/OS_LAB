#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    int numbers[4];

    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Opening FIFO for writing\n");
    pipe_fd = open(FIFO_NAME, open_mode);

    if (pipe_fd != -1) {
        printf("Enter 4 integers:\n");
        for (int i = 0; i < 4; i++) {
            scanf("%d", &numbers[i]);
        }

        write(pipe_fd, numbers, sizeof(numbers));
        close(pipe_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Producer finished\n");
    exit(EXIT_SUCCESS);
}
