#include <stdio.h>
#include <stdlib.h>

#include "wav_types.h"

int get_samples_per_channel(union header_data *header_bytes);

void reverse_data(short *data, union header_data *header_bytes) {

  int num_samples_per_channel = get_samples_per_channel(header_bytes);
  short num_channels = header_bytes->header.num_channels.short_value;

  int i, j;
  short temp;
  int end = (num_samples_per_channel - 1) * num_channels;
  for (i = 0; i < num_samples_per_channel/2; i++) 
    for (j = 0; j < num_channels; j++) {
      temp = data[i*num_channels + j];
      data[i*num_channels + j] = data[end - i * num_channels + j];
      data[end - i * num_channels + j] = temp;
    }
}

void mute(short *data, union header_data *header_bytes, char channel) {
  int num_samples_per_channel = get_samples_per_channel(header_bytes);
  short num_channels = header_bytes->header.num_channels.short_value;

  
  
}

int get_samples_per_channel(union header_data *header_bytes) {
  int num_samples_per_channel;
  
  short num_channels = header_bytes->header.num_channels.short_value;
  short bits_per_sample = header_bytes->header.bits_per_sample.short_value;
  int data_size = header_bytes->header.subchunk2_size.int_value;
  int bytes_per_sample = bits_per_sample / 8;

  num_samples_per_channel = data_size / bytes_per_sample / num_channels;

  return num_samples_per_channel;
}


