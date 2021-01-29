#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 44

typedef unsigned char byte;

union int_data {
  int int_value;
  byte int_bytes[4];
};

union short_data {
  short short_value;
  byte short_bytes[2];
};

struct header_struct {
  char chunk_id[4];
  union int_data chunk_size;
  char format[4];
  char subchunk1_id[4];
  union int_data subchunk1_size;
  union short_data audio_format;
  union short_data num_channels;
  union int_data sample_rate;
  union int_data byte_rate;
  union short_data block_align;
  union short_data bits_per_sample;
  char subchunk2_id[4];
  union int_data subchunk2_size;
};

union header_data {
  byte data[HEADER_SIZE];
  struct header_struct header;
};


void verify_machine(void);
int is_bigendian(void);
void verify_data(char *file_name, union header_data *file_bytes);
void reverse_numerical_bytes(union header_data *file_bytes);
void print_header_data(union header_data *file_bytes);

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
  
  int i;
  for (i = 0; i < HEADER_SIZE && (file_bytes->data[i] = getc(fp)) != EOF; i++)
    ;

  if (i != HEADER_SIZE) {
    fprintf(stderr, "Error: file %s header data incomplete\n", argv[1]);
    exit(3);
  }

  if (is_bigendian())
    reverse_numerical_bytes(file_bytes);
    
  verify_data(argv[1], file_bytes);
  print_header_data(file_bytes);

  fclose(fp);
  free(file_bytes);
  return 0;
}


/* Program works under the assumption that `int` is 4 bytes long
 * and `short` is 2 bytes long */
void verify_machine() {
  if (sizeof(int) != 4) {
    fprintf(stderr, "Error: machine data type INT isn't 4 bytes long\nCan't process wav header ");
    exit(4);
  }

  if (sizeof(short) != 2) {
    fprintf(stderr, "Error: machine data type SHORT isn't 2 bytes long\nCan't process wav header");
    exit(4);
  }

}


/* Machine should be little-endian to show header's numerical values correctly */
int is_bigendian() {
  union {
    char bytes[4];
    int val;
  } test;

  test.bytes[0] = 0;
  test.bytes[1] = 0;
  test.bytes[2] = 0;
  test.bytes[3] = 0xff;
 
  return test.val == 0xff;
}


void reverse(char *s, int len);

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

void reverse(char *s, int l) {
  char c;
  int i;
  for (i=0; i<l/2; i++) {
    c = s[i];
    s[i] = s[l-1-i];
    s[l-1-i] = c;
  }
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

