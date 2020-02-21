#include <stdio.h>

//#include "main.h"
#include "extern.h"

int aaa = 37;

int main(int argc, char* argv[]) {

  aaa = 98134;

  printf("aaa = %d\n", aaa);

  //int aaa = 37;
  aaa = 37;

  printf("aaa = %d\n", aaa);

  foo();

  printf("aaa = %d\n", aaa);

  printf("\n\n");

  return 0;
}

