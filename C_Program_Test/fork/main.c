#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int child_status = 0, status = 1;

    pid_t PID1 = fork();

    status = 2;
    pid_t PID2 = fork();

    switch (PID2) {
        case -1:
            printf("for error\n");
            break;
        case 0:
            printf("this is child process, PID1 = %d, PID2 = %d, status = %d\n",
                    PID1, PID2, status);
            child_status = 8;
            //sleep(1);
            return child_status;
            break;
        default:
            wait(&child_status);
            printf("this is parent process, PID1 = %d, PID2 = %d, child_status = %d vs. %d, status = %d\n",
                    PID1, PID2, child_status, WEXITSTATUS(child_status), status);
            break;
    }

    return 0;
}

