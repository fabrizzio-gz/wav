#ifndef WAV_DATA_H
#define WAV_DATA_H

void read_data(FILE *fp_in, union header_data *header_bytes, short *data[]);
void write_wav(FILE *fp_out, union header_data *header_bytes, short *data[]);

#endif

