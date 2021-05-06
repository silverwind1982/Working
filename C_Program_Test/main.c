#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    char *slot_s = "";
    int slot = -1;

    printf("\033[0;32;41mhello\033[0m\n");

    slot = atoi(slot_s);
    printf("slot_s: %s(%lu), slot = %d\n", slot_s, strlen(slot_s), slot);
    
    slot_s = "0";
    slot = atoi(slot_s);
    printf("slot_s: %s(%lu), slot = %d\n", slot_s, strlen(slot_s), slot);
    
    slot_s = "1";
    slot = atoi(slot_s);
    printf("slot_s: %s(%lu), slot = %d\n", slot_s, strlen(slot_s), slot);
    

    return 0;
}

