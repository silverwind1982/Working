#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

  FILE *pfile;
  char image[30] = {'\0'};
  char buffer[300] = {'\0'};
  char platName[30] = {'\0'};
  const char * tmp;

  pfile = popen("cat ./cmdline", "r");

  if (pfile) {
    fscanf(pfile, "BOOT_IMAGE=%s", image);

    fgets(buffer, sizeof(buffer), pfile);
    //printf("buffer: %s\n", buffer);

    if (tmp = strstr(buffer, "q_platform")) {
      //printf("tmp: %s\n", tmp);
      sscanf(tmp, "q_platform=%s", platName);
    }
    pclose(pfile);
  }
  
  printf("image: %s, platform: %s.\n", image, platName);
  printf("\n\n");

  return 0;
}

