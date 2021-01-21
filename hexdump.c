#include <stdio.h>

/* Prints the hex characters of a file */
int main(int argc, char *argv[]) {
  FILE *fp;
  char c;
  int count = 0, limit = 0;
  int i = 0;
  
  if (argc != 2) {
    printf("Usage: hexdump <file>\n");
    return 1;
  }

  fp = fopen(argv[1], "r");

  while ((c = getc(fp)) && i++ < 16) {
    printf("%x ", c);
  }
    
  
  return 0;
}
