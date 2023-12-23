#include <iostream>
#include <thread>

#include "./Include/BinarySearch.h"

void* binary_search(void *param)
{
    thread_param *p = (thread_param *)param;
    int *arr = p->arr;
    size_t left = p->left;
    size_t right = p->right;
    int target = p->target;
    int *result = p->result;
    int tmp = -1;
    pthread_mutex_t *mutex = p->mutex;
    pthread_cond_t *cond_var = p->cond_var;
    sem_t *sem = p->param_sem;
    int ready = 1;
    sem_post(sem);


    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            tmp = mid;
            break;
        }
        else if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

#ifdef MUTEX_SYNC
    pthread_mutex_lock(mutex);
#endif

#ifdef COND_SYNC
    if(ready == 1)
        pthread_cond_signal(cond_var);
#endif

    if (tmp > -1 && tmp != *result)
        *result = tmp;

#ifdef COND_SYNC
    while(ready == 0)
        pthread_cond_wait(cond_var, mutex);
#endif

#ifdef MUTEX_SYNC
    pthread_mutex_unlock(mutex);
#endif

#ifdef PROP_SYNC
    std::this_thread::sleep_for(std::chrono::seconds(1000));
#endif
    return NULL;

}
