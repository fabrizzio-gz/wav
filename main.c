#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wav_types.h"
#include "wav_header.h"
#include "wav_data.h"
#include "wav_process.h"
#include "helper_functions.h"

#define REVERSE 1
#define PRINT 1 << 1
#define WRITE 1 << 2
#define MUTE_LEFT 1 << 3
#define MUTE_RIGHT 1 << 4
#define CONTROL_VOLUME 1 << 5

/*TODO
 *Verify reverse works on mono too.
 */


int main(int argc, char *argv[]) {
  FILE *fp_in = NULL, *fp_out = NULL;
  char *input_file_name;
  char *output_file_name = NULL;
  char *volume_control = 0; // Positive or Negative
  char flags = 0;

  verify_machine();
  
  if (argc < 2) {
    printf("Usage: wave [flags] <file>\n");
    return 1;
  }

  /* Process flags */
  int i;
  for (i=1; i < argc ; i++) {
    if (*argv[i] == '-') {
      if (strlen(argv[i]) != 2) {
        fprintf(stderr, "Invalid option: %s\n", argv[i]);
        return 1;
      }
      switch (argv[i][1]) {
      case 'h':
        print_help();
        return 0;
      case 'r':
        flags |= REVERSE;
        flags |= WRITE;
        break;
      case 'v':
        flags |= CONTROL_VOLUME;
        flags |= WRITE;
        break;
      case 'o':
        flags |= WRITE;
        i++;
        if (i < argc && *argv[i] != '-')
          // Verify the file doesn't exit
          if (fopen(argv[i], "r") == NULL)
            output_file_name = argv[i];
          else {
            fprintf(stderr, "Invalid output file.\n"
                    "File %s already exists\n", argv[i]);
            return 1;
          } 
        else {
          fprintf(stderr, "Specify a valid output file name after -o flag\n");
          return 1;
        }
        break;
      case 'p':
        flags |= PRINT;
        break;
      case 'L':
        flags |= MUTE_LEFT;
        flags |= WRITE;
        break;
      case 'R':
        flags |= MUTE_RIGHT;
        flags |= WRITE;
        break;
      default:
        fprintf(stderr, "Invalid option: %s\n", argv[i]);
        return 1;
      }
    } else {
      static int first_file = 1;
      if (first_file) {
        fp_in = fopen(argv[i], "r");
        input_file_name = argv[i];
        first_file = 0;
        if (fp_in == NULL) {
          fprintf(stderr, "Error: Invalid file or path: %s\n", argv[i]);
          return 2;
        }
      } else {
          fprintf(stderr, "Error: Only one input file can be processed\n");
          return 2;
      }
    }
  }

  if (fp_in == NULL) {
    fprintf(stderr, "Specify an input file\n"
            "Usage: wave [flags] <file>\n");
    return 2;
  }

  /* Print wave file header by default if no
   * flags are given */
  if (argc == 2 && fp_in)
    flags |= PRINT;

  union header_data *header;
  short *data;
  
  header = (union header_data *) malloc(sizeof(union header_data));
  read_header(fp_in, header, input_file_name);

  if (flags & PRINT)
    print_header_data(header);

  if (flags & WRITE)
    data = read_data(fp_in, header);
  
  if (flags & REVERSE)
    reverse_data(data, header);

  if (flags & MUTE_LEFT)
    mute_left(data, header);

  if (flags & MUTE_RIGHT)
    mute_right(data, header);

  if (flags & CONTROL_VOLUME)
    control_volume(data, header);

  if (flags & WRITE) {
    if (!output_file_name)
      output_file_name = "output.wav";
    fp_out = fopen(output_file_name, "w"); 
    write_wav(fp_out, header, data, output_file_name);
  }
  
  fclose(fp_in);
  free(header);
  if (fp_out)
    fclose(fp_out);
  if (flags & WRITE)
    free(data);
  
  return 0;
}

