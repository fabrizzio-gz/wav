#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 44

typedef char byte;

struct header_struct {
  char chunk_id[4];
  int chunk_size;
};


/* Print the header of a .wav file */
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

  byte file_bytes[HEADER_SIZE];
  int i;
  for (i = 0; i < HEADER_SIZE && (file_bytes[i] = getc(fp)) != EOF; i++)
    ;


  struct header_struct *header = &file_bytes;

  printf("%.4s\n", header->chunk_id);
  printf("%d\n", header->chunk_size);

  return 0;
}
