#include <pthread.h>

typedef struct {
  unsigned int id;
  pthread_t pthread;
} miniomp_thread_t;

extern pthread_key_t miniomp_specifickey;

void miniomp_thread_init(miniomp_thread_t * thread, unsigned int id, void (*fn) (void *), void *data);
