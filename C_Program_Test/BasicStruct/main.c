#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* pointer;
} NODE, BBB;

struct Node1 {
    int data;
    struct Node1* pointer;
} xxx, yyy, zzz;

int main(int argc, char* argv[]) {

    NODE aaa, help, bbb;
    printf("aaa.data = %d\n", aaa.data);

    printf("help.data = %d\n", help.data);

    printf("bbb.data = %d\n", bbb.data);


    printf("xxx.data = %d\n", xxx.data);
    printf("yyy.data = %d\n", yyy.data);
    printf("zzz.data = %d\n", zzz.data);
    printf("\n\n");

    int i, j, k;

    printf("i = %d, j = %d, k = %d\n", i, j, k);


    return 0;
}

