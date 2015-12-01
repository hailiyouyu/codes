#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int status, i;

  pid = fork();
  if (pid == -1) {
    perror("fork error");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {           // child process
    
  } else {                  // parent process
    
  }

  for (i = 0; i < 100; ++i) {
    printf("Number %2d from Process %ld\n", i, (long)getpid());
  }
  exit(EXIT_SUCCESS);
}
