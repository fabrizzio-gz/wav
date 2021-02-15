main debug: helper_functions.c helper_functions.h main.c wav_data.c wav_data.h wav_header.c wav_header.h wav_types.h wav_process.c wav_process.h
	gcc -g main.c helper_functions.c wav_data.c wav_header.c wav_process.c -o wave

clean:
	rm wave
