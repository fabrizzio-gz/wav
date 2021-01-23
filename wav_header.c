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


void verify_machine(void);
void verify_data(char *file_name, union header_data *file_bytes);
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
    
  verify_data(argv[1], file_bytes);
  print_header_data(file_bytes);

  fclose(fp);
  free(file_bytes);
  return 0;
}


int is_bigendian(void); 

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

  if (is_bigendian())
    printf("Warning: machine isn't little endian\n"
           "Numerical values of the header will show incorrect values");
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
  printf("ChunkSize: %d\n", file_bytes->header.chunk_size);
  printf("Format: %.4s\n", file_bytes->header.format);
  printf("Subchunk1 ID: %.4s\n", file_bytes->header.subchunk1_id);
  printf("Subchunk1 Size: %d\n", file_bytes->header.subchunk1_size);
  printf("Audio Format: %d\n", file_bytes->header.audio_format);
  printf("Num Channels: %d\n", file_bytes->header.num_channels);
  printf("Sample Rate: %d\n", file_bytes->header.sample_rate);
  printf("ByteRate: %d\n", file_bytes->header.byte_rate);
  printf("Block Align: %d\n", file_bytes->header.block_align);
  printf("Bits per sample: %d\n", file_bytes->header.bits_per_sample);
  printf("Subchunk2 Id: %.4s\n", file_bytes->header.subchunk2_id);
  printf("Subchunk2 size: %d\n", file_bytes->header.subchunk2_size);
  
}

