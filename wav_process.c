#include <stdio.h>
#include <stdlib.h>

#include "wav_types.h"

int get_samples_per_channel(union header_data *header_bytes);
void mute(short *data, union header_data *header_bytes, char channel);

void reverse_data(short *data, union header_data *header_bytes) {

  int num_samples_per_channel = get_samples_per_channel(header_bytes);
  short num_channels = header_bytes->header.num_channels.short_value;

  int i, j;
  short temp;
  int end = (num_samples_per_channel - 1) * num_channels;
  printf("Reversing samples...");
  for (i = 0; i < num_samples_per_channel/2; i++) 
    for (j = 0; j < num_channels; j++) {
      temp = data[i*num_channels + j];
      data[i*num_channels + j] = data[end - i * num_channels + j];
      data[end - i * num_channels + j] = temp;
    }
  printf(" done.\n");
}

void mute_left(short *data, union header_data *header_bytes) {
  mute(data, header_bytes, 'l');
}

void mute_right(short *data, union header_data *header_bytes) {
  mute(data, header_bytes, 'r');
}

void mute(short *data, union header_data *header_bytes, char channel) {
  int num_samples_per_channel = get_samples_per_channel(header_bytes);
  short num_channels = header_bytes->header.num_channels.short_value;

  if (num_channels != 2) {
    fprintf(stderr, "Mute possible with 2 channels\n"
            "Input file has %d channel(s)\n", num_channels);
    exit(7);
  }

  printf("Muting %s channel...", channel == 'l' ? "left": "right");
  // Left channel comes first, then right channel.
  int channel_index = channel == 'l' ? 0 : 1;
  int i;
  for (i = 0; i < num_samples_per_channel; i++)
    data[num_channels*i + channel_index] = 0;
  printf(" done.\n");
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


