#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define NUM_THREADS 2 
#define MAX_COUNT 3
 
/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;
 
/* shared data between threads */
int count;
pthread_mutex_t count_lock;
pthread_cond_t count_cond = PTHREAD_COND_INITIALIZER;

void *thr_func1(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  
  /* thread code blocks here until MAX_COUNT is reached */
  printf("Hi, I'm thr_func1 with thread id: %d\n", data->tid);
  printf("I'll be waiting until MAX_COUNT is reached.\n");
  pthread_mutex_lock(&count_lock);
    while (count < MAX_COUNT) {
      pthread_cond_wait(&count_cond, &count_lock);
    }
  pthread_mutex_unlock(&count_lock);
  /* proceed with thread execution */
  printf("Thr_func1 over here. I'm done waiting. Here is the count: %d\n", count);

  pthread_exit(NULL);
}

/* some other thread code that signals a waiting thread that MAX_COUNT has been reached */
void *thr_func2(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;

  printf("Hi, I'm thr_func2 with thread id: %d\n", data->tid);
  /* some code here that does interesting stuff and modifies count */
  while(count < MAX_COUNT){
    pthread_mutex_lock(&count_lock);
    count++;
    printf("I just updated the count by 1\n");
    if (count == MAX_COUNT) {
      pthread_mutex_unlock(&count_lock);
      pthread_cond_signal(&count_cond);
    } else {
      pthread_mutex_unlock(&count_lock);
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  pthread_t thr[NUM_THREADS];
  int i, rc;

  /* create a thread_data_t argument array */
  thread_data_t thr_data[NUM_THREADS];
 
  /* initialize shared data */
  count = 0;
 
  /* initialize pthread mutex protecting "count" */
  pthread_mutex_init(&count_lock, NULL);
 
  /* initialize thread function pointer array */
   void *(*thr_func_ptr_arr[])(void*) = {thr_func1, thr_func2};

  /* create threads */
  for (i = 0; i < NUM_THREADS; ++i) {
    thr_data[i].tid = i;
    thr_data[i].stuff = (i + 1) * NUM_THREADS;
    if ((rc = pthread_create(&thr[i], NULL, (*thr_func_ptr_arr[i]), &thr_data[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }
  /* block until all threads complete */
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thr[i], NULL);
  }
 
  return EXIT_SUCCESS;
}
