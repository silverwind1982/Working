#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_length(char* string) {
    char *tmp = string;
    while (*(tmp++) != '\0') {
    }

    return (tmp - string - 1);
}


int main(int argc, char* argv[]) {

    char* sss = "this is ";
    char* tt1 = "this is a string";
    char* tt2 = "this is";
    char* tt3 = "this is ";

#if 0
    char *string = "this is a book";
    char *int_string = "abcde13";

    printf("the length of string is %d\n", string_length(string));

    printf("the value of int_string is %d\n", atoi(int_string));
#endif

    if (!strcmp(sss, tt1)) {
        printf("\"%s\" and \"%s\" in strcmp return 0\n", sss, tt1);
    } else {
        printf("\"%s\" and \"%s\" in strcmp return NOT 0\n", sss, tt1);
    }

    if (!strcmp(sss, tt2)) {
        printf("\"%s\" and \"%s\" in strcmp return 0\n", sss, tt2);
    } else {
        printf("\"%s\" and \"%s\" in strcmp return NOT 0\n", sss, tt2);
    }

    if (!strcmp(sss, tt3)) {
        printf("\"%s\" and \"%s\" in strcmp return 0\n", sss, tt3);
    } else {
        printf("\"%s\" and \"%s\" in strcmp return NOT 0\n", sss, tt3);
    }

    return 0;
}
