#include <stdio.h>

int main(int argc, char* argv[]) {
  FILE *file;

#if 0
  file = fopen("data.txt", "w");
  fprintf(file, "%s\t%d\n", "Mike", 30);
  fprintf(file, "%s\t%d\n", "Tank", 18);
  fclose(file);
#endif

  file = fopen("data.txt", "r");;
  char name[50];
  int age;
#if 0
  while(fscanf(file, "name:%s age:%d", name, &age) != EOF){
    char *tempName = name;  //依序得到姓名資料
    int tempAge = age;      //依序得到年齡資料

    printf("name: %s, age: %d\n", name, age);
  }
#endif

  //fscanf(file, "name:%s %*s %*s %*s %*s age:%d", name, &age);
  fscanf(file, "name:%s %*s age:%d", name, &age);

  printf("name: %s, age: %d\n", name, age);

  fclose(file);
  return 0;
}
