#include <stdio.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SelectSort(int* data, int len) {

    int i, j;

    for (i = 0; i < len; ++i) {
        for (j = i+1; j < len+1; ++j) {
            if (data[i] < data[j]) {
                swap(&data[i], &data[j]);
            }
        }
#if 1
        for (int k = 0; k <= len; ++k) {
            printf("data[%d] = %d ", k, data[k]);
        }
        printf("\n");
#endif
    }
}

void InsertionSort(int* data, int len) {

    int i, j, tmp;

    for (i = 1; i <= len; ++i) {
        tmp = data[i];
        for (j = i; j > 0; --j) {
            if (tmp > data[j-1]) {
                data[j] = data[j-1];
            } else {
                break;
            }
        }
        data[j] = tmp;
#if 1
        for (int k = 0; k <= len; ++k) {
            printf("data[%d] = %d ", k, data[k]);
        }
        printf("\n");
#endif
    }
}

void BubbleSort(int* data, int len) {

    int i, j, flag = 1;

    for (j = len; j > 0 && flag; --j) {
        flag = 0;
        for (i = 0; i < j; ++i) {
            if (data[i] < data[i+1]) {
                swap(&data[i], &data[i+1]);
                flag = 1;
            }
        }
#if 1
        for (int k = 0; k <= len; ++k) {
            printf("data[%d] = %d ", k, data[k]);
        }
        printf("\n");
#endif
    }
}

int main(int argc, char* argv[]) {

    int data[] = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6};
    int length = 9;

    //SelectSort(data, length);
    InsertionSort(data, length);
    //BubbleSort(data, length);

#if 0
    printf("data = %p\n", data);
    printf("&data[0] = %p\n", &data[0]);
    printf("&data[1] = %p\n", &data[1]);
    printf("&data[2] = %p\n", &data[2]);
#endif

    printf("data:");
    for (int k = 0; k <= length; ++k) {
        printf(" %d", data[k]);
    }
    printf("\n");

    return 0;
}
