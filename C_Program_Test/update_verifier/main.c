#include <stdio.h>
#include <string.h>

#include "boot_control.h"

int main(int argc, char* argv[]) {
	int result = 0;

    mark_boot_successful();
    printf("result = %d\n", result);

	return 0;
}

