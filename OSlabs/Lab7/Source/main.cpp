#include <pthread.h>
#include <semaphore.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#include "./Include/BinarySearch.h"
#include "./Include/HandleInput.h"

size_t constexpr ARR_SIZE = 10000000;
int constexpr TARGET = 42;

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