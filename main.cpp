#include <chrono>
#include <corecrt_wstdio.h>
#include <iostream>
#include <stdio.h>
#include <thread>

int times = 360;
int sleep = 500;
char *line = (char *)"This is a line!";
char *line_other = (char *)"This is other line!";
FILE *input = NULL;
char *input_file = NULL;
FILE *output = stdout;
FILE *output_other = NULL;
char *output_file = NULL;

bool check_arg(char *param, char const *is_short, char const *or_long) {
  return (strcmp(param, is_short) == 0 || strcmp(param, or_long) == 0);
}

void parse_args(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (check_arg(argv[i], "-e", "---stderr")) {
      output = stderr;
    } else if (check_arg(argv[i], "-a", "--alternate")) {
      output_other = stderr;
    } else if (check_arg(argv[i], "-t", "--times")) {
      if (i < argc - 1) {
        times = atoi(argv[i + 1]);
        i++;
      }
    } else if (check_arg(argv[i], "-s", "--sleep")) {
      if (i < argc - 1) {
        sleep = atoi(argv[i + 1]);
        i++;
      }
    } else if (check_arg(argv[i], "-l", "--line")) {
      if (i < argc - 1) {
        line = argv[i + 1];
        i++;
      }
    } else if (check_arg(argv[i], "-i", "--input")) {
      if (i < argc - 1) {
        if (strcmp(argv[i + 1], "stdin") == 0) {
          input = stdin;
        } else {
          input_file = argv[i + 1];
        }
        i++;
      }
    } else if (check_arg(argv[i], "-o", "--output")) {
      if (i < argc - 1) {
        output_file = argv[i + 1];
        i++;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  parse_args(argc, argv);
  if (output_file) {
    errno_t error = fopen_s(&output, output_file, "w");
    if (error > 0) {
      std::cerr << "Could not open the output file.\n";
      return 1;
    }
  }
  fprintf(output, "LongWrite starting...\n");
  if (input_file) {
    errno_t error = fopen_s(&input, input_file, "r");
    if (error > 0) {
      std::cerr << "Could not open the input file.\n";
      return 1;
    }
  }
  if (input) {
    fprintf(output, "We'll write all the lines from input until EOF.\n");
    int ch = getc(input);
    while (ch != EOF) {
      fprintf(output, "%c", ch);
      fflush(output);
      ch = getc(input);
    }
    fclose(input);
  } else {
    fprintf(output, "We'll write one line %d times at each %d miliseconds.\n",
            times, sleep);
    for (int i = 0; i < times; i++) {
      if (output_other && i % 2 != 0) {
        fprintf(output_other, "%s\n", line_other);
        fflush(output_other);
      } else {
        fprintf(output, "%s\n", line);
        fflush(output);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
  }
  fclose(output);
}
