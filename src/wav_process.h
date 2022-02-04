#ifndef WAV_PROCESS_H
#define WAV_PROCESS_H

void reverse_data(short *data, union header_data *header_bytes);
void mute_left(short *data, union header_data *header_bytes);
void mute_right(short *data, union header_data *header_bytes);
void control_volume(short *data, union header_data *header_bytes);

#endif
