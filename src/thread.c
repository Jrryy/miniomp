#include "thread.h"
#include "libminiomp.h"

pthread_key_t miniomp_specifickey;

void miniomp_thread_init(miniomp_thread_t * thread, unsigned int id, void (*fn) (void *), void *data){
  thread->id = id;
  thread->region = data;
  pthread_create(thread->pthread, NULL, fn, data);
  pthread_setspecific(miniomp_specifickey, thread);
}
