#include <stdio.h>

#include "wav_types.h"

void read_data(FILE *fp_in, union header_data *header_bytes, short *data[]){
  short num_channels = header_bytes->header.num_channels.short_value;
  short bits_per_sample = header_bytes->header.bits_per_sample.short_value;
  int data_size = header_bytes->header.subchunk2_size.int_value;

  printf("Read data output\n");
  printf("Num channels: %hi\n", num_channels);
  printf("Bits per samples: %hi\n", bits_per_sample);
  printf("Data size: %d\n", data_size);
}

void write_wav(FILE *fp_out, union header_data *header_bytes, short *data[]) {
  fwrite(header_bytes, sizeof(union header_data), 1, fp_out);
}


