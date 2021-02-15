main: helper_functions.c helper_functions.h main.c wav_data.c wav_data.h wav_header.c wav_header.h wav_types.h
	gcc main.c helper_functions.c wav_data.c wav_header.c -o main

clean:
	rm main
