#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wav_types.h"
#include "wav_header.h"
#include "helper_functions.h"


// void verify_machine(void);

/* Print header data of a .wav file */
int main(int argc, char *argv[]) {
  FILE *fp;

  verify_machine();
  
  if (argc != 2) {
    printf("Usage: wave <file>\n");
    return 1;
  }

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    fprintf(stderr, "Error: Invalid file or path: %s\n", argv[1]);
    return 2;
  }

  union header_data *file_bytes = (union header_data *) malloc(sizeof(union header_data));

  read_header(fp, file_bytes, argv[1]);

  fclose(fp);
  free(file_bytes);
  return 0;
}

