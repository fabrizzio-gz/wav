#include <stdio.h>
#include <stdlib.h>


void print_help() {
  printf("Usage: wave file\n"
         "   or: wave [OPTIONS] file\n"
         "Print wave wave file header data or modify it.\n\n"
         "Options:\n"
         "  -h                print help and exit\n"
         "  -L                mute left channel (stereo only)\n"
         "  -o OUTPUT_FILE    specify output file name\n"
         "  -p                print header information\n"
         "  -r                reverse sound samples\n"
         "  -R                mute right channel (stereo only)\n"
         "\n"
         "This utility is used to print canonical (44 bytes) header information \n"
         "of .wav files. It can also perform simple operations such as reverse \n"
         "audio samples or mute channels on 16-bit samples wave files. If no \n"
         "flags are given, this utility will print the header information by \n"
         "default.\n"
         "\n"
         "When options to alter the origiinal wave file are passed to the \n"
         "utility, the original file is preserved. All of the changes are \n"
         "written to the file `output.wav`. If this file already exists, it's \n"
         "overwritten. When an output filename is specified, it will verify that\n"
         "the file does not exist. If it exists, the utility will exit without\n"
         "overwritting it.\n");
}

/* Program works under the assumption that `int` is 4 bytes long
 * and `short` is 2 bytes long */
void verify_machine() {
  if (sizeof(int) != 4) {
    fprintf(stderr, "Error: machine data type INT isn't 4 bytes long\nCan't process wav header ");
    exit(4);
  }

  if (sizeof(short) != 2) {
    fprintf(stderr, "Error: machine data type SHORT isn't 2 bytes long\nCan't process wav header");
    exit(4);
  }
}


/* Machine should be little-endian to show header's numerical values correctly */
int is_bigendian() {
  union {
    char bytes[4];
    int val;
  } test;

  test.bytes[0] = 0;
  test.bytes[1] = 0;
  test.bytes[2] = 0;
  test.bytes[3] = 0xff;
 
  return test.val == 0xff;
}


/* Reverse in-place `l` elements of array `s` */
void reverse(char *s, int l) {
  char c;
  int i;
  for (i=0; i<l/2; i++) {
    c = s[i];
    s[i] = s[l-1-i];
    s[l-1-i] = c;
  }
}
