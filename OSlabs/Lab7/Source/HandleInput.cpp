#include <iostream>
#include <thread>

#include "./Include/HandleInput.h"

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