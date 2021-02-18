#ifndef WAV_DATA_H
#define WAV_DATA_H

short *read_data(FILE *fp_in, union header_data *header_bytes);
void write_wav(FILE *fp_out, union header_data *header_bytes, short *data, char *file_name);

#endif

