#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    unsigned int integer = 0xabcd;
    unsigned char buf[4];
    int i;

    memcpy(buf, &integer, sizeof(integer));

    printf("integer = %08x\n", integer);

    for (i = 0; i < 4; ++i) {
        printf("buf[%d]@%p = %02x\n", i, &buf[i], buf[i]);
    }

    printf("\n");
    if ((integer & 0xff) == (unsigned int)buf[0]) {
        printf("This is little endian. (%02x)\n", integer & 0xff);
    } else {
        printf("This is big endian. (%02x)\n", integer & 0xff);
    }
    printf("\n");

    return 0;
}

