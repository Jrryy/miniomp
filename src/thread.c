#include "thread.h"
#include "libminiomp.h"

void miniomp_thread_init(miniomp_thread_t * thread, unsigned int id, void (*fn) (void *), void *data){
  thread->id = id;
  pthread_create(thread->pthread, NULL, fn, data);
  pthread_setspecific(miniomp_specifickey, thread);
}
