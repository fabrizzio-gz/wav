#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wav_types.h"
#include "wav_header.h"
#include "wav_data.h"
#include "helper_functions.h"


/* Print header data of a .wav file */
int main(int argc, char *argv[]) {
  FILE *fp_in, *fp_out;

  verify_machine();
  
  if (argc != 2) {
    printf("Usage: wave <file>\n");
    return 1;
  }

  fp_in = fopen(argv[1], "r");

  if (fp_in == NULL) {
    fprintf(stderr, "Error: Invalid file or path: %s\n", argv[1]);
    return 2;
  }

  union header_data *header_bytes = (union header_data *) malloc(sizeof(union header_data));
  read_header(fp_in, header_bytes, argv[1]);

  short *data = read_data(fp_in, header_bytes);

  fp_out = fopen("output.wav", "w");

  
  write_wav(fp_out, header_bytes, data);

  fclose(fp_in);
  fclose(fp_out);
  free(header_bytes);
  free(data);
  // free(data);
  return 0;
}

