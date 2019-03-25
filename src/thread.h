#include <pthread.h>
#include "libminiomp.h"

typedef struct {
  unsigned int id;
  pthread_t pthread;
} miniomp_thread;

void miniomp_thread_init(miniomp_thread * thread, unsigned int id);
