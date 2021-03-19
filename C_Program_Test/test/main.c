#include <stdio.h>

int main(int argc, char* argv[]) {

    int i = 2782, j;

    if (argc > 1) {
    }

    for (j = 20; j < 50; ++j) {
        printf("%d, %d\n", j, j*i);
    }


    return 0;
}

