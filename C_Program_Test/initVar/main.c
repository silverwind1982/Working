#include <stdio.h>
#include <stdlib.h>

struct simple_struct {
  int a;
  float b;
  char c;
  struct simple_struct* np;
};

//int* value = (int*) malloc(sizeof(int) * 3);  // error: initializer element is not constant
int* value;

struct simple_struct sa;
//struct simple_struct* psa = (struct simple_struct*) malloc(sizeof(struct simple_struct) * 3);  // error: initializer element is not constant

int g_int;

static int g_s_int;

int main(int argc, char* argv[]) {

  int dynamic_int;
  static int s_int;

  value = (int*) malloc(sizeof(int) * 3);  // error: initializer element is not constant

  printf("undefined global int = %d\n\n", g_int);  // should be 0

  printf("undefined global static int = %d\n\n", g_s_int);  // should be 0

  printf("undefined static int = %d\n\n", s_int);  // should be 0

  printf("undefined int = %d\n", dynamic_int);  // can be any value

  printf("\n\n");

  return 0;
}

