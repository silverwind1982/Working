#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//#define DEVFILE "/dev/devone"
#define DEVFILE "/dev/devtwo"
#define DEVCOUNT 4

int open_file(char* filename)
{
    int fd;

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
    }
    return fd;
}

void close_file(int fd)
{
    printf("%s called\n", __func__);
    if (close(fd) != 0) {
        perror("close");
    }
}

int main(int argc, char *argv[])
{
    int fd[DEVCOUNT];
    int i;
    char file[BUFSIZ];

    for (i = 0; i < DEVCOUNT; ++i) {
        snprintf(file, sizeof(file), "%s%d", DEVFILE, i);
        printf("opening %s\n", file);
        fd[i] = open_file(file);
    }

    sleep(2);

    for (i = 0; i < DEVCOUNT; ++i) {
        printf("closing fd[%d]\n", i);
        close_file(fd[i]);
    }

    return 0;
}
