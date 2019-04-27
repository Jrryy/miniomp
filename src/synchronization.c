#include "libminiomp.h"

// Default lock for critical sections
pthread_mutex_t miniomp_default_lock;

void GOMP_critical_start (void) {
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  pthread_mutex_lock(&(thread->region->mutex));
  //printf("TBI: Entering an unnamed critical, don't know if anyone else is alrady in. I proceed\n");
}

void GOMP_critical_end (void) {
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  pthread_mutex_unlock(&(thread->region->mutex));
  //printf("TBI: Exiting an unnamed critical section. I can not inform anyone else, bye!\n");
}

void GOMP_critical_name_start (void **pptr) {
  pthread_mutex_t * plock = pptr;
  //printf("Arrived to pointer to name %p\n", plock);

  //miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  //miniomp_parallel_t *region = thread->region;
  
  //pthread_setspecific(miniomp_specifickey, thread);
  pthread_mutex_lock(plock);
  //printf("TBI: Entering a named critical %p (%p)\n", pptr, plock);
  // if plock is NULL it means that the lock associated to the name has not yet been allocated and initialized
}

void GOMP_critical_name_end (void **pptr) {
  pthread_mutex_t * plock = pptr;
  //printf("Arrived to pointer to name %p\n", plock);
  pthread_mutex_unlock(plock);
  //printf("TBI: Exiting a named critical %p (%p)\n", pptr, plock);
  // if plock is still NULL something went wrong
}

pthread_barrier_t miniomp_barrier;

void GOMP_barrier() {
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  printf("Thread %d waiting for signal\n", thread->id);
  pthread_barrier_wait(&(thread->region->barrier));
  
}
