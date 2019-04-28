#include "libminiomp.h"

miniomp_single_t miniomp_single;

bool
GOMP_single_start (void)
{
  miniomp_thread_t *thread = pthread_getspecific(miniomp_specifickey);
  unsigned int id = omp_get_thread_num();
  if (thread->region->single == NULL){
    miniomp_single.id = id;
    thread->region->single = &miniomp_single;
    return(true);
  }
  else {
    if(thread->region->single->id == id){
      return(true);
    }
    else{
      return(false);
    }
  }
}
