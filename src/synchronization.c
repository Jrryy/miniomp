#include "libminiomp.h"

// Default lock for critical sections
pthread_mutex_t miniomp_default_lock;

void GOMP_critical_start (void) {
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  pthread_mutex_lock(&(thread->region->mutex));
}

void GOMP_critical_end (void) {
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  pthread_mutex_unlock(&(thread->region->mutex));
}

void GOMP_critical_name_start (void **pptr) {
  pthread_mutex_t * plock = pptr;
  pthread_mutex_lock(plock);
}

void GOMP_critical_name_end (void **pptr) {
  pthread_mutex_t * plock = pptr;
  pthread_mutex_unlock(plock);
}

pthread_barrier_t miniomp_barrier;

void GOMP_barrier() {
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  pthread_barrier_wait(&(thread->region->barrier));
}
