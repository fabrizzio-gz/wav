main debug: src/helper_functions.c src/helper_functions.h src/main.c src/wav_data.c src/wav_data.h src/wav_header.c src/wav_header.h src/wav_types.h src/wav_process.c src/wav_process.h
	gcc src/main.c src/helper_functions.c src/wav_data.c src/wav_header.c src/wav_process.c -o wave

clean:
	rm wave
