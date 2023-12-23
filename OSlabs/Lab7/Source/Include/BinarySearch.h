#include <pthread.h>
#include <semaphore.h>


struct thread_param
{
    int *arr;
    size_t left;
    size_t right;
    int target;
    int *result;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond_var;
    sem_t *param_sem;

};

extern "C" void* binary_search(void *param);