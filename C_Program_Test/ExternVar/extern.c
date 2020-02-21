#include <stdio.h>

#include "main.h"

int foo() {
  printf("aaa in foo() = %d\n", aaa);

  aaa = 1614;
  return aaa;
}

