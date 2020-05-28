#include <stdio.h>

int main(int argc, char* argv[]) {

  int aaa = 612345;
  char* bbb = "abcdg.hijoiajsdfpsdfjioasjdfiasjf";
  float ccc = 12.5678978361276234;

  printf("%u|\n", aaa);
  printf("%x|\n", aaa);
  printf("%13x|\n", aaa);
  printf("%13.10x|\n", aaa);  // precision specifies the minimum number of digits to be written, if shorter the result is padded
  printf("%-13x|\n", aaa);
  printf("%013x|\n", aaa);
  printf("\n\n");

  printf("%13s|\n", bbb);
  printf("%-13s|\n", bbb);
  printf("%-13.7s|\n", bbb);  // precision specifies the maximum number of characters to be printed
  printf("%13.7s|\n", bbb);  // precision specifies the maximum number of characters to be printed
  printf("\n\n");

  printf("%13f|\n", ccc);
  printf("%-13f|\n", ccc);
  printf("%013f|\n", ccc);
  printf("%-9.3f|\n", ccc);  // precision specifies the number of digits to be printed after the decimal point
  printf("%9.3f|\n", ccc);
  printf("\n\n");

  return 0;
}

