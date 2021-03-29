#include <stdio.h>

typedef struct test0 test0;

struct test0
{
	int a;
	int b;
	int c;
};

struct test1
{
	int a : 4;
	int b : 4;
	int c : 1;
};

struct test2
{
	short a : 9;
	short b : 3;
};

struct test3
{
	char a : 4;
	char b : 3;
};

struct test4
{
	char a : 6;
	short b : 15;
};

int main(int argc, char* argv[]) {

    test0 tt;
    struct test1 aa;
    /*struct test2 bb;
    struct test3 cc;
    struct test4 dd;*/

    printf("test1: %lu\ntest2: %lu\ntest3: %lu\ntest4: %lu\n",
            sizeof(struct test1), sizeof(struct test2), sizeof(struct test3), sizeof(struct test4));

#if 0
    tt.a = aa.a = 7;
    tt.b = aa.b = 12;
    tt.c = aa.c = 1;
#else
    aa.a = tt.a = 7;
    aa.b = tt.b = 12;
    aa.c = tt.c = 1;
#endif

    printf("tt.a = %d, tt.b = %d, tt.c = %d\n", tt.a, tt.b, tt.c);
    printf("aa.a = %d, aa.b = %d, aa.c = %d\n", aa.a, aa.b, aa.c);

    return 0;
}

