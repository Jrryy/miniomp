#include <pthread.h>

// Declaration of array for storing pthread identifiers from pthread_create function

// Type declaration for parallel descriptor (arguments needed to create pthreads)
typedef struct {
  void (*fn) (void *);
  void *fn_data;
  unsigned int id;
  pthread_mutex_t mutex;
    // complete the definition of parallel descriptor
} miniomp_parallel_t;

extern miniomp_parallel_t *miniomp_parallel;

// Declaration of per-thread specific key
extern pthread_key_t miniomp_specifickey;

// Functions implemented in this module
void miniomp_parallel_init(miniomp_parallel_t *parallel, void (*fn) (void *), void *data, unsigned int id);
void GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags);
