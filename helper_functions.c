#include <stdio.h>
#include <stdlib.h>


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
