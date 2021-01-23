#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 44

typedef char byte;

struct header_struct {
  char chunk_id[4];
  int chunk_size;
  char format[4];
  char subchunk1_id[4];
  int subchunk1_size;
  short audio_format;
  short num_channels;
  int sample_rate;
  int byte_rate;
  short block_align;
  short bits_per_sample;
  char subchunk2_id[4];
  int subchunk2_size;
};

union header_data {
  byte data[HEADER_SIZE];
  struct header_struct header;
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

  union header_data *file_bytes = (union header_data *) malloc(sizeof(union header_data));
  int i;
  for (i = 0; i < HEADER_SIZE && (file_bytes->data[i] = getc(fp)) != EOF; i++)
    ;

  printf("%.4s\n", file_bytes->header.chunk_id);
  printf("%d\n", file_bytes->header.chunk_size);
  printf("%.4s\n", file_bytes->header.format);
  printf("%.4s\n", file_bytes->header.subchunk1_id);
  printf("%d\n", file_bytes->header.subchunk1_size);
  printf("%d\n", file_bytes->header.audio_format);
  printf("%d\n", file_bytes->header.num_channels);
  printf("%d\n", file_bytes->header.sample_rate);
  printf("%d\n", file_bytes->header.byte_rate);
  printf("%d\n", file_bytes->header.block_align);
  printf("%d\n", file_bytes->header.bits_per_sample);
  printf("%.4s\n", file_bytes->header.subchunk2_id);
  printf("%d\n", file_bytes->header.subchunk2_size);

  return 0;
}
