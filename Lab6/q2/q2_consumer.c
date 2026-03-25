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
    int open_mode = O_RDONLY;
    int numbers[4];

    printf("Opening FIFO for reading\n");
    pipe_fd = open(FIFO_NAME, open_mode);

    if (pipe_fd != -1) {
        res = read(pipe_fd, numbers, sizeof(numbers));
        close(pipe_fd);

        if (res > 0) {
            printf("Received integers:\n");
            for (int i = 0; i < 4; i++) {
                printf("%d ", numbers[i]);
            }
            printf("\n");
        }
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Consumer finished\n");
    exit(EXIT_SUCCESS);
}
