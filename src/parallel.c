#include "libminiomp.h"

// This file implements the PARALLEL construct

// Declaration of array for storing pthread identifier from pthread_create function
pthread_t *miniomp_threads;

// Global variable for parallel descriptor
miniomp_parallel_t *miniomp_parallel;

// Declaration of per-thread specific key
pthread_key_t miniomp_specifickey;

// This is the prototype for the Pthreads starting function
void *worker(void *args) {
  miniomp_parallel_t *parallel_t = args;
  int id = parallel_t->id;
  printf("Thread %d initialized\n", id);
  void (*fn) (void *) = parallel_t->fn;
  void * data = parallel_t->fn_data;
  pthread_setspecific(miniomp_specifickey, parallel_t);
  fn(data);
    // insert all necessary code here for:
  //   1) save thread-specific data
  //   2) invoke the per-threads instance of function encapsulating the parallel region
  //   3) exit the function
  return(NULL);
}

void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
  if(!num_threads) num_threads = omp_get_num_threads();
  printf("Starting a parallel region using %d threads\n", num_threads);
  miniomp_threads = malloc(num_threads*sizeof(pthread_t));
  miniomp_parallel = malloc(sizeof(miniomp_parallel_t)*num_threads);
  for (int i=0; i<num_threads; i++){
    //pthread_mutex_init(&miniomp_parallel[i].mutex, NULL);
    miniomp_parallel[i].fn = fn;
    miniomp_parallel[i].fn_data = data;
    miniomp_parallel[i].id = i;
    pthread_create(&miniomp_threads[i], NULL, worker, &miniomp_parallel[i]);
  }
  for (int i=0; i < num_threads; i++){
    pthread_join(miniomp_threads[i], NULL);
    //pthread_mutex_destroy(&miniomp_parallel[i].mutex);
  }
  free(miniomp_threads);
  free(miniomp_parallel);
}
