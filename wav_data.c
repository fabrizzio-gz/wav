#include <stdio.h>

#include "wav_types.h"

void write_wav(FILE *fp_out, union header_data *header_bytes, short *data_bytes[]);


void write_wav(FILE *fp_out, union header_data *header_bytes, short *data_bytes[]) {
  fwrite(header_bytes, sizeof(union header_data), 1, fp_out);
}
