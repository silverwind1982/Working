#include <stdio.h>

int main(int argc, char* argv[]) {

  char buffer[50] = {0};
  char buffer2[50] = {0};
  printf("%s\n", "hello");
  printf("%10s%s\n", "hello", "ab");
  printf("%10s%s\n", "", "ab");

  snprintf(buffer, sizeof(buffer), "%20s", "hello");
  printf("buffer1: %s\n", buffer);

  snprintf(buffer2, sizeof(buffer2), "%-40s", buffer);
  printf("buffer2: %s\n", buffer2);

  snprintf(buffer, sizeof(buffer), "%20s", "hellohellohellohellohellohello");
  printf("buffer1: %s\n", buffer);

  snprintf(buffer2, sizeof(buffer2), "%-40s", buffer);
  printf("buffer2: %s\n", buffer2);

  return 0;
}

