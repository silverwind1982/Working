#include <stdio.h>

int sum = 0;

int all_single_value(int target) {


#if 0
    printf("target = %d, sum = %d\n", target, sum);
    sum += target % 10;
    if (target / 10) {
        all_single_value(target / 10);
        return sum;
    } else {
        return target;
    }
#elif 1
    int sum = target % 10;
    printf("target = %d, sum = %d\n", target, sum);
    if (target / 10) {
        printf("return all_single_value(%d) + %d\n", target / 10, sum);
        return all_single_value(target / 10) + sum;
    } else {
        printf("return %d\n", target);
        return target;
    }
#else
    if (target / 10) {
        printf("all_single_value(%d) + %d\n", target / 10, target % 10);
        return all_single_value(target / 10) + (target % 10);
    } else {
        printf("all_single_value(%d) = %d\n", target, target);
        return target;
    }
#endif
}

int main(int argc, char* argv[]) {

    int target = 7283719;

    printf("sum of all value is %d\n", all_single_value(target));

    return 0;
}

