#ifndef WAV_PROCESS_H
#define WAV_PROCESS_H

void reverse_data(short *data, union header_data *header_bytes);
void mute(short *data, union header_data *header_bytes, char channel);

#endif
