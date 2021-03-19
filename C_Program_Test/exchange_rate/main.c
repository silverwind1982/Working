#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    float rate = 27.82, sum = 0, left = 0;
    int amount = 0, times = 0;

    if (argc > 1) {
        rate = atof(argv[1]);
    }

    while (times < 50) {
        do {
            ++amount;
            sum = rate * amount;
        } while (sum < 500);

        if ((left = (sum - (int)sum)) < 0.5) {
            printf("$%2d => %8.02f", amount, sum);

            if (left > 0.4) {
                printf(" **");
            } else if (left > 0.3) {
                printf(" *");
            }
            printf("\n");
        }
        ++times;
    }

    return 0;
}

