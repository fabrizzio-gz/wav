#include <stdio.h>
#include <stdlib.h>

#include "wav_types.h"

short *read_data(FILE *fp_in, union header_data *header_bytes){
  short *data;
  
  short num_channels = header_bytes->header.num_channels.short_value;
  short bits_per_sample = header_bytes->header.bits_per_sample.short_value;
  int data_size = header_bytes->header.subchunk2_size.int_value;
  
  printf("Read data output\n");
  printf("Num channels: %hi\n", num_channels);
  printf("Bits per samples: %hi\n", bits_per_sample);
  printf("Data size: %d\n", data_size);

  if (bits_per_sample != 16) {
    fprintf(stderr, "Error: Samples are not short type");
    exit(5);
  }

  int bytes_per_sample = bits_per_sample / 8;
  int num_samples_per_channel = data_size / bytes_per_sample / num_channels;

  data = (short *) malloc(num_samples_per_channel * num_channels * sizeof(short));
  

  if (data == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory for samples\n");
    exit(6);
  }

  int i, j;
  short *dp = data;
  for (i=0; i < num_samples_per_channel; i++) {
    for (j=0; j < num_channels; j++) {
      if (fread(dp, bytes_per_sample, 1, fp_in) != 1) {
        fprintf(stderr, "Error: Couldn't read all samples\n");
        exit(6);
      }  
      dp++;
    }
  }
  
  printf("Bytes per sample: %d\n", bytes_per_sample);
  return data; 
}

void write_wav(FILE *fp_out, union header_data *header_bytes, short *data[]) {
  fwrite(header_bytes, sizeof(union header_data), 1, fp_out);
}


