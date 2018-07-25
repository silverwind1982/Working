#include <stdio.h>
#include <stdarg.h>


void Print(char* format, ...) {
  int i;
  va_list args;

  va_start(args, format);

#if 0  // use va_arg to parse arguments
  for (i = 0; i < 5; ++i) {
    int val = va_arg(args, int);
    printf("%d ", val);
  }
#elif 0
  printf(format, args);
#elif 0
  char buf[1024] = {0};
  vsprintf(buf, format, args);
  printf("%s\n\n", buf);
#else
  char buf[1024] = {0};
  vsnprintf(buf, sizeof(buf), format, args);
  printf("%s\n\n", buf);
#endif

  va_end(args);
};

int main(int argc, char* argv[]) {

  Print("%d, %d, %d, %d, %d", 3, 9, 8, 11, 5);

  printf("\n\n");

  return 0;
}

