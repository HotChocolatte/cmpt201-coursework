#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *line = NULL;
  size_t len = 0;
  ssize_t numchars = 0;

  char *saveptr;

  while (numchars != 1) {
    printf("Please enter some text: ");

    numchars = getline(&line, &len, stdin);

    if (numchars == -1) {
      printf("Error or end of file reached.\n");
    } else if (numchars == 1) {
      printf("Submission empty; stopping program");
      break;
    } else {
      printf("Tokens:");
      char *ret = strtok_r(line, " ", &saveptr);
      while (ret != NULL) {
        printf("\n%s", ret);
        ret = strtok_r(NULL, " ", &saveptr);
      }
    }
  }
  free(line);
  return 0;
}
