#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int main() {
  cout << "LongWrite starting...\n";
  cout << "We will write one line each half second for three minutes...\n";
  FILE *file;
  errno_t error = fopen_s(&file, "longwrite.txt", "w");
  if (error > 0) {
    cout << "Could not open the file.\n";
    return 1;
  }
  for (int i = 0; i < 360; ++i) {
    fprintf(file, "This is a line.\n");
    fflush(file);
    cout << "Wrote one line.\n";
    this_thread::sleep_for(chrono::milliseconds(500));
  }
  fclose(file);
}
