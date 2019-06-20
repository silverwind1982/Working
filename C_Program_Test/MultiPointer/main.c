#include <stdio.h>
#include <stdlib.h>

void noPointer(int value) {
  value = 7;
}

void singlePointer(int* value) {
  *value = 17;
}

void doublePointer(int** value) {
  *value = (int*) malloc(sizeof(int) * 1);
  **value = 27;
}

void triplePointer(int*** value) {
  *value = (int**) malloc(sizeof(int*) * 1);
  **value = (int*) malloc(sizeof(int) * 1);
  ***value = 37;
}

void quadPointer(int**** value) {
  *value = (int***) malloc(sizeof(int**) * 1);
  **value = (int**) malloc(sizeof(int*) * 1);
  ***value = (int*) malloc(sizeof(int) * 1);
  ****value = 47;
}

int main(int argc, char* argv[]) {
  int value;
  int* p_value;
  int** pp_value;
  int*** ppp_value;

  noPointer(value);
  printf("value = %d\n", value);

  singlePointer(&value);
  printf("value = %d\n", value);

  doublePointer(&p_value);
  printf("p_value = %d\n", *p_value);

  triplePointer(&pp_value);
  printf("pp_value = %d\n", **pp_value);

  quadPointer(&ppp_value);
  printf("ppp_value = %d\n", ***ppp_value);

  printf("\n\n");

  if (p_value) {
    free(p_value);
  }

  if (*pp_value) {
    if (**pp_value) {
      free(*pp_value);
    }
    free(pp_value);
  }

  if (*ppp_value) {
    if (**ppp_value) {
      if (***ppp_value) {
        free(**ppp_value);
      }
      free(*ppp_value);
    }
    free(ppp_value);
  }

  return 0;
}

