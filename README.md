# WAV utility

Retrieve WAVE (.wav) files header information and perform simple manipulations.

- Only "canonical" (44-bytes) headers are supported.
- Only 16-bit audio samples of one or two channels are supported.

## Compilation

Compile as:

```
$ gcc main.c helper_functions.c wav_data.c wav_header.c wav_process.c -o wave
```

Alternatively, run Makefile:

```
$ make
```

## Usage

Print the header information:

```
./wave file.wave
```

Execute modifications and write on a new file with the following options:

- `-L`, to mute left channel.
- `-o OUTPUTFILE`, to specifiy ouput filename.
- `-p`, to print the header information.
- `-r`, to reverse the audio samples.
- `-R`, to mute right channel.

### Example

To reverse audio samples and mute left channel:

```
./wave -r -L my_file.wav
```

