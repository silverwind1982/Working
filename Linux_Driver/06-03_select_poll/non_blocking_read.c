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

#define DEVFILE "/dev/devone0"

int main(int argc, char *argv[])
{
    int fd;
    unsigned char buf[64];
    ssize_t sz;
    int i;

    fd = open(DEVFILE, 0, O_RDWR | O_NONBLOCK);
    printf("read() ... %x vs. %x\n", O_RDWR, O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

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

    close(fd);

    return 0;
}
