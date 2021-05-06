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
#include <sys/ioctl.h>
#include <poll.h>

#define DEVFILE "/dev/devone0"

int main(int argc, char *argv[])
{
    int fd;
    struct pollfd fds[3];
    int retval;
    unsigned char buf[64];
    ssize_t sz;
    int i;

    fd = open(DEVFILE, 0, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    do {
        fds[0].fd = fd;
        fds[0].events = POLLIN;

        printf("poll() ...\n");
        retval = poll(fds, 1, 1 * 1000);
        if (retval == -1) {
            perror("poll");
            break;
        }

        if (retval) {
            break;
        }
    } while (retval == 0);

    if (fds[0].revents & POLLIN) {
        printf("read() ...\n");
        sz = read(fd, buf, sizeof(buf));
        printf("read() %zu\n", sz);
        if (sz > 0) {
            for (i = 0; i < sz; ++i) {
                printf("%02x ", buf[i]);
            }
            printf("\n");
        } else {
            printf("errno %d\n", errno);
            perror("read");
        }
    }

    close(fd);

    return 0;
}
