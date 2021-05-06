#include <stdio.h>

int execute(int a, int b, int operator) {
    switch (operator) {
        case 0:
            return a + b;
            break;
        case 1:
            return a - b;
            break;
        case 2:
            return a * b;
            break;
        case 3:
            return a / b;
            break;
        case 4:
            return a % b;
            break;
        default:
            return a + b;
            break;
    }
}

int func1(int a, int b, int (*function)(int, int, int)) {
    int operator = 0;
    for (operator = 0; operator < 6; ++operator) {
        printf("operator: %d, result is: %d\n", operator, function(a, b, operator));
    }
    return 0;
}

typedef int (*function_def)(int, int, int);

int perform(int a, int b, int operator) {
    switch (operator) {
        case 0:
            return a + b;
            break;
        case 1:
            return a - b;
            break;
        case 2:
            return a * b;
            break;
        case 3:
            return a / b;
            break;
        case 4:
            return a % b;
            break;
        default:
            return a + b;
            break;
    }
}

int func2(int a, int b, function_def func_def) {
    int operator = 0;
    for (operator = 0; operator < 6; ++operator) {
        printf("operator: %d, result is: %d\n", operator, func_def(a, b, operator));
    }
    return 0;
}

int main(int argc, char* argv[]) {

    int a = 41, b = 17;

    func1(a, b, execute);

    func2(a, b, perform);

    return 0;
}

