#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
  cout << "LongWrite starting...\n";
  cout << "We will write one line each half second for three minutes...\n";
  FILE *file;
  file = fopen("longwrite.txt", "w");
  for (int i = 0; i < 360; ++i) {
	  fprintf(file, "This is a line.\n");
	  fflush(file);
	  cout << "Wrote one line.\n";
	  this_thread::sleep_for(chrono::milliseconds(500));
  }
  fclose(file);
}
