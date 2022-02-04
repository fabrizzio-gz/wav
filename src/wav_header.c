#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "wav_types.h"
#include "helper_functions.h"


void verify_data(char *file_name, union header_data *file_bytes);
void reverse_numerical_bytes(union header_data *file_bytes);
void print_header_data(union header_data *file_bytes);


void read_header(FILE *fp, union header_data *file_bytes, char *file_name) {
  int i;
  for (i = 0; i < HEADER_SIZE && (file_bytes->data[i] = getc(fp)) != EOF; i++)
    ;

  if (i != HEADER_SIZE) {
    fprintf(stderr, "Error: file %s header data incomplete\n", file_name);
    exit(3);
  }

  if (is_bigendian())
    reverse_numerical_bytes(file_bytes);

  verify_data(file_name, file_bytes);
  
}


void verify_data(char *file_name, union header_data *file_bytes) {

  /* Need to copy char array to another buffer because the
  *  end char '\0' isn't present */
  char text[5];
  text[4] = '\0';
  if (strcmp(strncpy(text, file_bytes->header.chunk_id, 4), "RIFF") != 0) {
    fprintf(stderr, "Error: file %s isn't in RIFF (WAV container) format\n", file_name);
    exit(3);
  }

  if (strcmp(strncpy(text, file_bytes->header.format, 4), "WAVE") != 0) {
    fprintf(stderr, "Error: file %s isn't in WAVE format", file_name);
    exit(3);
  }

  if (strcmp(strncpy(text, file_bytes->header.subchunk2_id, 4), "data") != 0) {
    fprintf(stderr, "Error: file %s header is not in canonical form\n"
           "Extra or missing header data\n", file_name);
    exit(3);
  }
}


void reverse_numerical_bytes(union header_data *file_bytes) {
  reverse(file_bytes->header.chunk_size.int_bytes, 4);
  reverse(file_bytes->header.subchunk1_size.int_bytes, 4);
  reverse(file_bytes->header.audio_format.short_bytes, 2);
  reverse(file_bytes->header.num_channels.short_bytes, 2);
  reverse(file_bytes->header.sample_rate.int_bytes, 4);
  reverse(file_bytes->header.byte_rate.int_bytes, 4);
  reverse(file_bytes->header.block_align.short_bytes, 2);
  reverse(file_bytes->header.bits_per_sample.short_bytes, 2);
  reverse(file_bytes->header.subchunk2_size.int_bytes, 4);
}


void print_header_data(union header_data *file_bytes) {
  
  printf("ChunkID: %.4s\n", file_bytes->header.chunk_id);
  printf("ChunkSize: %d\n", file_bytes->header.chunk_size.int_value);
  printf("Format: %.4s\n", file_bytes->header.format);
  printf("Subchunk1 ID: %.4s\n", file_bytes->header.subchunk1_id);
  printf("Subchunk1 Size: %d\n", file_bytes->header.subchunk1_size.int_value);
  printf("Audio Format: %d\n", file_bytes->header.audio_format.short_value);
  printf("Num Channels: %d\n", file_bytes->header.num_channels.short_value);
  printf("Sample Rate: %d\n", file_bytes->header.sample_rate.int_value);
  printf("ByteRate: %d\n", file_bytes->header.byte_rate.int_value);
  printf("Block Align: %d\n", file_bytes->header.block_align.short_value);
  printf("Bits per sample: %d\n", file_bytes->header.bits_per_sample.short_value);
  printf("Subchunk2 Id: %.4s\n", file_bytes->header.subchunk2_id);
  printf("Subchunk2 size: %d\n", file_bytes->header.subchunk2_size.int_value);
}

