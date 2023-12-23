#include <pthread.h>
#include <semaphore.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>


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

struct handle_input_params
{
    pthread_t *tid;
    size_t size;
};

static void* binary_search(void *param)
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

void *handle_input(void *prm)
{
    //pthread_t *arr = (pthread_t *)tid;
    handle_input_params *tmp = (handle_input_params *)prm;
    pthread_t* arr = tmp->tid;
    size_t thread_count = tmp->size;

    while(true){
        int thread_id;
        std::cout << "Enter the thread ID (0 to " << thread_count - 1 << ") to set properties: ";
        std::cin >> thread_id;

        if (thread_id < 0 || thread_id >= thread_count) {
            std::cerr << "Invalid thread ID!" << std::endl;
            return nullptr;
        }

        std::cout << "Enter new thread priority (0-99): ";
        int priority;
        std::cin >> priority;

        struct sched_param param;
        param.sched_priority = priority;

        // Set thread priority
        if (pthread_setschedparam(arr[thread_id], SCHED_FIFO, &param) != 0) {
            std::cerr << "Unable to set thread priority!" << std::endl;
        }

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);

        int num_cores = std::thread::hardware_concurrency();

        std::cout << "Enter the thread ID (0 to " << thread_count - 1 << ") to set affinity: ";
        std::cin >> thread_id;

        std::cout << "Enter the number of CPU cores (0-" << num_cores - 1 << ") for thread affinity: ";
        int core;
        std::cin >> core;

        for (size_t i = 0; i < core; i++)
        {
            CPU_SET(i, &cpuset);
        }
        

        // Set thread affinity
        if (pthread_setaffinity_np(arr[thread_id], sizeof(cpu_set_t), &cpuset) != 0) {
            std::cerr << "Unable to set thread affinity!" << std::endl;
        }

        std::cout << "Enter the thread ID (0 to " << thread_count - 1 << ") to detach: ";
        std::cin >> thread_id;
        if (pthread_detach(arr[thread_id]) != 0) {
                std::cerr << "Failed to detach thread " << thread_id << "!" << std::endl;
                // Handle detach error if needed
            }
        

        std::cout << "Enter the thread ID (0 to " << thread_count - 1 << ") to cancel: ";
        std::cin >> thread_id;
        if (pthread_cancel(arr[thread_id]) != 0) {
                    std::cerr << "Failed to cancel thread " << thread_id << "!" << std::endl;
                    // Handle cancellation error if needed
                }


    }
    return NULL;
}

size_t constexpr ARR_SIZE = 10000000;
int constexpr TARGET = 42;

void sort(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
        
    }
    
}

int main()
{
    std::vector<int> arr(ARR_SIZE);
    std::srand(time(NULL));
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % (100 - -100 + 1) + -100;
    }
    //sort(arr, ARR_SIZE);
    std::sort(arr.begin(), arr.end());

    thread_param th_param;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    sem_t param_sem;
    pthread_cond_t cond_var;
    sem_init(&param_sem, 0, 0);
    pthread_cond_init(&cond_var, NULL);

    size_t thread_count = 1;
    std::cout << "Enter the thread count: ";
    std::cin >> thread_count;

    int result = -1;
    th_param.arr = arr.data();
    th_param.mutex = &mutex;
    th_param.cond_var = &cond_var;
    th_param.param_sem = &param_sem;
    th_param.target = TARGET;
    th_param.result = &result;

    pthread_t *tid = new pthread_t[thread_count + 1];
    int partition_size = ARR_SIZE / thread_count;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < thread_count; ++i) {
        th_param.left = i * partition_size;
        th_param.right = (i == thread_count - 1) ? (ARR_SIZE - 1) : ((i + 1) * partition_size - 1);
        pthread_create(&tid[i], NULL, binary_search, &th_param);
        sem_wait(&param_sem);
    }

    handle_input_params hip;
    hip.tid = tid;
    hip.size = thread_count;

#ifdef PROP_SYNC
    pthread_create(&tid[thread_count], NULL, handle_input, &hip);
#endif

    for (size_t i = 0; i < thread_count; i++)
    {
        pthread_join(tid[i], NULL);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time(end - start);
    

    /*for (size_t i = 0; i < ARR_SIZE; i++)
    {
        std::cout << arr[i] << ' ';
    }*/
    std::cout << std::endl;
    
    std::cout << "Searched index: "<< result << std::endl;
    std::cout << time.count() << std::endl;

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);
    sem_destroy(&param_sem);


    return 0;
}