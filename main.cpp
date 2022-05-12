#include <chrono>
#include <iostream>
#include <thread>

bool is_param_of(char *param, char const *short_kind, char const *long_kind) {
  return (strcmp(param, short_kind) == 0 || strcmp(param, long_kind) == 0);
}

int main(int argc, char *argv[]) {
  int times = 360;
  int sleep = 500;
  char *file_name = NULL;
  char *line = (char *)"This is a line!";
  for (int i = 1; i < argc - 1; i++) {
    if (is_param_of(argv[i], "-t", "--times")) {
      times = atoi(argv[i + 1]);
    } else if (is_param_of(argv[i], "-s", "--sleep")) {
      sleep = atoi(argv[i + 1]);
    } else if (is_param_of(argv[i], "-f", "--file")) {
      file_name = argv[i + 1];
    } else if (is_param_of(argv[i], "-l", "--line")) {
      line = argv[i + 1];
    }
  }
  std::cout << "LongWrite starting...\n";
  std::cout << "We will write one line " << times << " times at each " << sleep
            << " miliseconds...\n";
  if (file_name) {
    FILE *file;
    errno_t error = fopen_s(&file, file_name, "w");
    if (error > 0) {
      std::cerr << "Could not open the file.\n";
      return 1;
    }
    for (int i = 0; i < times; i++) {
      fprintf(file, "%s\n", line);
      fflush(file);
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
    fclose(file);
  } else {
    for (int i = 0; i < times; i++) {
      std::cout << line << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
  }
}
