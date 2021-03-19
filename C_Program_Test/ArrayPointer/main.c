#include <stdio.h>
#include <stdlib.h>

void function(int* data) {

}

void function_d(int** data) {

    *data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; ++i) {
        (*data)[i] = i;
    }
}


int main(int argc, char* argv[]) {

    int data[] = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6};

    function(data);

    printf("data = %p\n", data);
    printf("&data[0] = %p\n", &data[0]);
    printf("&data[1] = %p\n", &data[1]);
    printf("&data[2] = %p\n", &data[2]);



    int* data_d;
    function_d(&data_d);

    printf("data_d = %p\n", data_d);
    printf("data_d[0] = %d\n", data_d[0]);
    printf("data_d[1] = %d\n", data_d[1]);
    printf("data_d[2] = %d\n", data_d[2]);


    return 0;
}
