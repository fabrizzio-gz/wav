#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void get_4bytes(FILE *fp, char * destination);

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
  get_4bytes(fp, chunkId);
  chunkId[5] = '\0';
    
  if (strcmp(chunkId, "RIFF") != 0) {
    printf("Error: File %s isn't in RIFF format\n", argv[1]);
    return 3;
  }

  /* Get file size: 4 bytes */
  char size_bytes[4];
  get_4bytes(fp, size_bytes);
  /* This works only on little endian machines */
  int *size = &size_bytes;
  printf("File size is: %d\n", *size + 8);

  /* Verify it's a WAV file  */
  

  printf("OK\n");
  fclose(fp);
  
  return 0;
}

void get_4bytes(FILE *fp, char *destination) {
  int file_char;
  int c = 0;
  while (c < 4 && (file_char = getc(fp)) != EOF) 
    destination[c++] = (char) file_char;

  /* Wasn't able to fetch 4 bytes */
  if (c != 4) {
    printf("Invalid file\n");
    exit(1);
  }
}
