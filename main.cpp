#include <chrono>
#include <corecrt_wstdio.h>
#include <iostream>
#include <stdio.h>
#include <thread>

int times = 360;
int sleep = 500;
char *file = NULL;
char *line = (char *)"This is a line!";
FILE *destiny = stdout;

bool check(char *param, char const *is_short, char const *or_long) {
  return (strcmp(param, is_short) == 0 || strcmp(param, or_long) == 0);
}

void parse(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (check(argv[i], "-e", "---stderr")) {
      destiny = stderr;
    } else if (check(argv[i], "-t", "--times")) {
      if (i < argc - 1) {
        times = atoi(argv[i + 1]);
        i++;
      }
    } else if (check(argv[i], "-s", "--sleep")) {
      if (i < argc - 1) {
        sleep = atoi(argv[i + 1]);
        i++;
      }
    } else if (check(argv[i], "-f", "--file")) {
      if (i < argc - 1) {
        file = argv[i + 1];
        i++;
      }
    } else if (check(argv[i], "-l", "--line")) {
      if (i < argc - 1) {
        line = argv[i + 1];
        i++;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  parse(argc, argv);
  if (file) {
    errno_t error = fopen_s(&destiny, file, "w");
    if (error > 0) {
      std::cerr << "Could not open the file.\n";
      return 1;
    }
  }
  fprintf(destiny, "LongWrite starting...\n");
  fprintf(destiny, "We'll write one line %d times at each %d miliseconds.\n",
          times, sleep);
  for (int i = 0; i < times; i++) {
    fprintf(destiny, "%s\n", line);
    fflush(destiny);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
  }
  fclose(destiny);
}
