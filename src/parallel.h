#include <pthread.h>

// Declaration of array for storing pthread identifiers from pthread_create function

typedef struct {
  unsigned int id; // id of the thread that reached the single part
} miniomp_single_t;

// Type declaration for parallel descriptor (arguments needed to create pthreads)
typedef struct {
  void (*fn) (void *);
  void *fn_data;
  unsigned int id;
  pthread_mutex_t mutex;
  pthread_barrier_t barrier;
  miniomp_single_t *single;
} miniomp_parallel_t;

typedef struct {
  unsigned int id;
  pthread_t pthread;
  miniomp_parallel_t *region;
} miniomp_thread_t;

extern miniomp_parallel_t *miniomp_parallel;
extern pthread_key_t miniomp_specifickey;

// Functions implemented in this module
void miniomp_parallel_init(miniomp_parallel_t *parallel, void (*fn) (void *), void *data, unsigned int id);
void miniomp_thread_init(miniomp_thread_t * thread, unsigned int id, void (*fn) (void *), miniomp_parallel_t *region);
void GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags);
