#include <stdio.h>

void aaa(int input = 0) {
    print("input = %d\n", input);
}

int main(int argc, char* argv[]) {

    aaa();
    aaa(1);


    return 0;
}

