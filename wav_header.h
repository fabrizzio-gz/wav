#ifndef WAV_HEADER_H
#define WAV_HEADER_H

void read_header(FILE *fp, union header_data *file_bytes, char *file_name);
void print_header_data(union header_data *file_bytes);

#endif
