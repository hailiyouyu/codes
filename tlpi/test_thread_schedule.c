#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_THREADS 2

void *thread_rountine(void *arg) {
  int i, status;
  for (int i = 0; i < 100; ++i) {
    printf("Number %2d from Thread %ld\n", i, (long) pthread_self());
    if (i == 50) {
      status = pthread_yield();
      if (status != 0) {
        perror("pthread_yield");
        pthread_exit(NULL);
      }
    }
  }
  pthread_exit(NULL);
}

int main(void) {
  pthread_t pid[NUM_OF_THREADS];
  int status, i;

  for (i = 0; i < NUM_OF_THREADS; ++i) {
    status = pthread_create(&pid[i], NULL, thread_rountine, NULL);
    if (status != 0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < NUM_OF_THREADS; ++i) {
    status = pthread_join(pid[i], NULL);
    if (status != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
