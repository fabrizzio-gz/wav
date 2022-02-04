# WAV

Perform simple manipulations to .wav files and retrieve its header information.

- Supports only "canonical" (44 bytes) headers and 16-bit audio simples with one or two channels.

## Compilation

Compile with make:

```
$ make
```

Alternatively:

```
$ gcc src/main.c src/helper_functions.c src/wav_data.c src/wav_header.c src/wav_process.c -o wave
```

Compilation will generate a executable file called `wave`.

## Usage

Execute modifications and write to a new file with the following options:

- `-L`, to mute left channel.
- `-o <outputfile>`, to specifiy ouput filename.
- `-p`, to print the header information.
- `-r`, to reverse the audio samples.
- `-R`, to mute right channel.

## Examples

Print the header information:

```
./wave my-file.wav
```

Mute left audio channel:

```
./wave -L my-file.wav
```

Mute right audio channel:

```
./wave -R my-file.wav
```

Reverse audio samples:

```
./wave -r my-file.wav
```

Multiple options can be chained. For example, to reverse audio samples and mute left channel:

```
./wave -r -L my_file.wav
```

## License

GPL
