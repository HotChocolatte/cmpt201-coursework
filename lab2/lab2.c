#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
      printf("Submission empty; stopping program.");
      break;
    } else {
      char *ret = strtok_r(line, "\n", &saveptr);
      if (strcmp(ret, "exit") == 0) {
        printf("Exiting...\n");
        break;
      } else if (strcmp(ret, "joke") == 0) {
        printf("You!\n");
        continue;
      }
      pid_t pid = fork();
      if (pid < 0) {
        perror("Failed to fork parent...");
        break;
      }
      if (pid == 0) {
        int execRet = execlp(ret, ret, (char *)NULL);
        if (execRet == -1) {
          printf("Exec failure.\n");
          break;
        }
      } else {
        waitpid(-1, NULL, 0);
      }
    }
  }
  free(line);
  return 0;
}
