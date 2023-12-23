#include <pthread.h>
#include <semaphore.h>

struct handle_input_params
{
    pthread_t *tid;
    size_t size;
};


extern "C" void *handle_input(void *prm);