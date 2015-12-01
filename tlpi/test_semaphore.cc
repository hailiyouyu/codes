#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#include <iostream>
#include <deque>

#define BUFFSIZE 10
#define MAXITEM 100

sem_t sem_pro, sem_con;
pthread_mutex_t pmutex;

typedef int item_type;
std::deque<item_type> buffer;

item_type produce_item() {
  srand(time(NULL));
  item_type item = rand() % MAXITEM;
  printf("Produce Item: %2d\n", item);
  return item;
}

void consume_item(item_type item) {
  printf("Consume Item: %2d\n", item);
}

void print_deque() {
  std::cout << "Deque: ";
  for (auto i = 0; i != buffer.size(); ++i)
    std::cout << buffer[i] << ' ';
  std::cout << '\n';
}

void *producer(void *arg) {
  for (int i = 0; i < 10; ++i) {
    item_type item = rand() % MAXITEM;
    sem_wait(&sem_pro);
    pthread_mutex_lock(&pmutex);
    printf("Produce Item: %2d\n", item);
    buffer.push_back(item);
    print_deque();
    pthread_mutex_unlock(&pmutex);
    sem_post(&sem_con);
  }
  return NULL;
}

void *consumer(void *arg) {
  for (int i = 0; i < 10; ++i) {
    sem_wait(&sem_con);
    pthread_mutex_lock(&pmutex);
    item_type item = buffer[0];
    printf("Consume Item: %2d\n", item);
    buffer.pop_front();
    print_deque();
    pthread_mutex_unlock(&pmutex);
    sem_post(&sem_pro);
  }
  return NULL;
}

int main() {
  pthread_t pids[2];
  void *(*thread_funs[2]) (void *);
  thread_funs[0] = producer;
  thread_funs[1] = consumer;
  
  int status, i;

  srand(time(0));
  
  status = pthread_mutex_init(&pmutex, NULL);
  if (status != 0) {
    perror("pthread_mutex_init");
    exit(EXIT_FAILURE);
  }

  status = sem_init(&sem_pro, 0, BUFFSIZE);
  if (status != 0) {
    perror("sem_init");
    exit(EXIT_FAILURE);
  }

  status = sem_init(&sem_con, 0, 0);
  if (status != 0) {
    perror("sem_init");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < 2; ++i) {
    status = pthread_create(&pids[i], NULL, thread_funs[i], NULL);
    if (status != 0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < 2; ++i) {
    status = pthread_join(pids[i], NULL);
    if (status != 0) {
      perror("pthread_join");
      exit(EXIT_SUCCESS);
    }
  }

  pthread_mutex_destroy(&pmutex);
  sem_destroy(&sem_pro);
  sem_destroy(&sem_con);
  exit(EXIT_SUCCESS);
}

