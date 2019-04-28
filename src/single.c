#include "libminiomp.h"

miniomp_single_t miniomp_single;

bool
GOMP_single_start (void)
{
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  unsigned int id = omp_get_thread_num();
  pthread_mutex_lock(&(thread->region->mutex));
  if (thread->region->single == NULL){
    miniomp_single.id = id;
    thread->region->single = &miniomp_single;
    pthread_mutex_unlock(&(thread->region->mutex));
    return(true);
  }
  else {
    if(thread->region->single->id == id){
      pthread_mutex_unlock(&(thread->region->mutex));
      return(true);
    }
    else{
      pthread_mutex_unlock(&(thread->region->mutex));
      return(false);
    }
  }
}
