#include <stdio.h>
#include <string.h>


/* Prints the hex characters of a file */
int main(int argc, char *argv[]) {
  FILE *fp;
  
  if (argc != 2) {
    printf("Usage: wave <file>\n");
    return 1;
  }

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Invalid file or path: %s\n", argv[1]);
    return 2;
  }

  /* Verify it's a RIFF file: 4 bytes */
  char chunkId[5];
  int file_char;
  int c = 0;
  while (c < 4 && (file_char = getc(fp)) != EOF) 
    chunkId[c++] = (char) file_char;
  
  if (strcmp(chunkId, "RIFF") != 0) {
    printf("Error: File %s isn't in RIFF format\n", argv[1]);
    return 3;
  }

  /* Get file size: 4 bytes */
  char size_bytes[4];
  c = 0;
  while (c < 4 && (file_char = getc(fp)) != EOF)
    size_bytes[c++] = (char) file_char;

  /* Works only on little endian machines */
  int *size = &size_bytes;

  printf("Size is: %d\n", *size + 8);

  printf("OK\n");
  fclose(fp);
  
  return 0;
}

