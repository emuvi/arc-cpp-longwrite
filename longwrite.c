#include <stdio.h>
#include <time.h>

int main() {
  printf("LongWrite starting...\n");
  printf("We will write one line each half second for three minutes...\n");
  FILE *file;
  file = fopen("longwrite.txt", "w");
  for (int i = 0; i < 360; ++i) {
	  fprintf(file, "this is a line...\n");
	  printf("wrote one line...\n");
	  nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
  }
  fclose(file);
}
