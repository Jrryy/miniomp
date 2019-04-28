#include "libminiomp.h"

// This file implements the PARALLEL construct

// Declaration of array for storing pthread identifier from pthread_create function
miniomp_thread_t *miniomp_threads;

// Global variable for parallel descriptor
miniomp_parallel_t *miniomp_parallel;

// Declaration of per-thread specific key
extern pthread_key_t miniomp_specifickey;

void miniomp_thread_init(miniomp_thread_t * thread, unsigned int id, void (*fn) (void *), miniomp_parallel_t *region){
  thread->id = id;
  thread->region = region;
  pthread_create(&(thread->pthread), NULL, fn, thread);
}


// This is the prototype for the Pthreads starting function
void worker(void *args) {
  miniomp_thread_t *thread = args;
  pthread_setspecific(miniomp_specifickey, thread);
  miniomp_parallel_t *parallel = thread->region;
  void (*fn) (void *) = parallel->fn;
  void * data = parallel->fn_data;
  fn(data);
}

void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
  if(!num_threads) num_threads = omp_get_num_threads();
  miniomp_threads = malloc(num_threads*sizeof(miniomp_thread_t));
  miniomp_parallel = malloc(sizeof(miniomp_parallel_t));
  miniomp_parallel->fn = fn;
  miniomp_parallel->fn_data = data;
  miniomp_parallel->id = 0;
  pthread_barrier_init(&(miniomp_parallel->barrier), NULL, num_threads);
  pthread_mutex_init(&(miniomp_parallel->mutex), NULL);
  pthread_key_create(&miniomp_specifickey, NULL);
  for (int i=0; i<num_threads; i++){
    miniomp_thread_init(&miniomp_threads[i], i, worker, miniomp_parallel);
  }
  for (int i=0; i < num_threads; i++){
    pthread_join(miniomp_threads[i].pthread, NULL);
  }
  pthread_mutex_destroy(&(miniomp_parallel->mutex));
  pthread_barrier_destroy(&(miniomp_parallel->barrier));
  free(miniomp_threads);
  free(miniomp_parallel);
}

