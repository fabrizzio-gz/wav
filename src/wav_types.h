#ifndef WAV_TYPES_H
#define WAV_TYPES_H

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

#endif
