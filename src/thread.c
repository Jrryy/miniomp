#include "thread.h"

void miniomp_thread_init(miniomp_thread * thread, unsigned int id, void (*fn) (void *), void *data){
  thread->id = id;
  pthread_create(thread->pthread, NULL, fn, data);
}
