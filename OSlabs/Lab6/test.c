#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <mutex>

pthread_rwlock_t rwlock; // Read-Write Lock
pthread_cond_t cv;       // Condition Variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool data_ready=false;
struct ThreadData
{
    int start;
    int end;
    int priority;
    pthread_t threadId;
};

std::vector<ThreadData> threadDataObjects;
std::vector<pthread_t> threadObjects; 

int sharedTotalOccurrences = 0;
void displayResults()
{
    std::cout << "Total occurrences of 'a' in the file: " << sharedTotalOccurrences << std::endl;
}
void countOccurrencesInThreadWithoutSync(ThreadData *data)
{
    int localOccurrences = 0;
    std::string filename = "text.txt";
    char targetChar = 's';

    std::ifstream file(filename, std::ios::binary);
    file.seekg(data->start);

    while (file.tellg() < data->end)
    {
        char c;
        if (file.get(c))
        {
            if (c == targetChar)
            {
            sharedTotalOccurrences ++;
            }
        }
        else
        {
            break;
        }
    }

    file.close();

    

    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
}

void countOccurrencesInThreadWithConditionVariable(ThreadData *data)
{
    int localOccurrences = 0;
    std::string filename = "text.txt";
    char targetChar = 's';

    std::ifstream file(filename, std::ios::binary);
    file.seekg(data->start);

    while (file.tellg() < data->end)
    {
        char c;
        if (file.get(c))
        {
            if (c == targetChar)
            {
                pthread_mutex_lock(&mutex);

                sharedTotalOccurrences += 1;

                pthread_cond_signal(&cv);
                data_ready=false;


                pthread_mutex_unlock(&mutex);
            }
        }
        else
        {
            break;
        }
    }

    file.close();

    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
}


void countOccurrencesInThreadWithRWLock(ThreadData *data)
{
    int localOccurrences = 0;
    std::string filename = "text.txt";
    char targetChar = 's';

    std::ifstream file(filename, std::ios::binary);
    file.seekg(data->start);

    while (file.tellg() < data->end)
    {
        char c;
        if (file.get(c))
        {
            if (c == targetChar)
            {
                 pthread_rwlock_wrlock(&rwlock);
    sharedTotalOccurrences += 1;
    pthread_rwlock_unlock(&rwlock);
            }
        }
        else
        {
            break;
        }
    }
    
    file.close();

    
    std::this_thread::sleep_for(std::chrono::milliseconds(100000));

    // Sleep for demonstration purposes (not recommended in a real scenario)
}
int getFileSize(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return -1;
    }

    std::streampos fileSize = file.tellg();
    file.close();

    if (fileSize == -1) {
        std::cerr << "Failed to get file size: " << filename << std::endl;
        return -1;
    }

    return static_cast<int>(fileSize);
}
 
void cancelThread(ThreadData *data)
{
    if (pthread_cancel(data->threadId) != 0)
    {
        std::cerr << "Failed to cancel thread." << std::endl;
    }
    else
    {
        std::cout << "Thread " << data->priority << " canceled successfully." << std::endl;
    }
}

void setThreadPriority(ThreadData *data, int newPriority)
{
    pid_t threadID;
    std::cin >> threadID;
    if (setpriority(PRIO_PROCESS, threadID, newPriority) != 0)
    {
        perror("setpriority");
        std::cerr << "Failed to set thread priority." << std::endl;
        return;
    }

    std::cout << "Thread priority updated successfully." << std::endl;
}
void exitThread(ThreadData *data)
{
    std::cout << "Thread " << data->priority << " exited." << std::endl;
}
void detach(const std::vector<pthread_t> &threadObjects)
{
    int threadIndex;
    std::cout << "Enter the thread index to detach: ";
    std::cin >> threadIndex;

    if (threadIndex >= 0 && threadIndex < threadObjects.size())
    {
        int res = pthread_detach(threadObjects[threadIndex]);
        if (res == 0)
        {
            std::cout << "Detached successfully." << std::endl;
        }
        else if (res == EINVAL)
        {
            std::cerr << "Invalid thread ID or already detached/terminated." << std::endl;
        }
        else if (res == ESRCH)
        {
            std::cerr << "No such process (thread not found or already detached)." << std::endl;
        }
        else
        {
            std::cerr << "Failed to detach thread. Error code: " << res << std::endl;
        }
    }
    else
    {
        std::cerr << "Invalid thread index." << std::endl;
    }
}





void *threadFunction(void *arg)
{
    ThreadData *data = static_cast<ThreadData *>(arg);
    countOccurrencesInThreadWithoutSync(data);
    pthread_exit(NULL);
}

int main()
{
    pthread_rwlock_init(&rwlock, NULL);
    pthread_cond_init(&cv, NULL);

    int numProcesses;

    std::cout << "How many threads would you like to use? ";
    std::cin >> numProcesses;

    if (numProcesses <= 0)
    {
        std::cerr << "Invalid number of threads. Please choose a positive integer." << std::endl;
        return 1;
    }

    std::ifstream file("text.txt", std::ios::binary | std::ios::ate);
    int fileSize = getFileSize("text.txt");
    if (fileSize == -1) {
        std::cerr << "Failed to get file size. Exiting." << std::endl;
        return 1;
    }
    file.close();

    int segmentSize = fileSize / numProcesses;
    int syncMethod;

    std::cout << "Choose synchronization method:" << std::endl;
    std::cout << "1. Without Synchronization" << std::endl;
    std::cout << "2. With Mutex and Condition Variable" << std::endl;
    std::cout << "3. With Read-Write Lock" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> syncMethod;
auto startTime = std::chrono::high_resolution_clock::now();

    
   for (int i = 0; i < numProcesses; ++i)
{
    ThreadData* data = new ThreadData(); // Allocate memory for each ThreadData

    data->start = i * segmentSize;
    data->end = (i == numProcesses - 1) ? fileSize : (i + 1) * segmentSize;
    data->priority = i + 1;

    threadDataObjects.push_back(*data);

    pthread_t thread;
    switch (syncMethod)
    {
    case 1:
        pthread_create(&thread, NULL, threadFunction, data);
        break;
    case 2:
    data_ready=true;
        pthread_create(&thread, NULL, reinterpret_cast<void *(*)(void *)>(countOccurrencesInThreadWithConditionVariable), data);
        break;
    case 3:
        pthread_create(&thread, NULL, reinterpret_cast<void *(*)(void *)>(countOccurrencesInThreadWithRWLock), data);
        break;
    default:
        std::cerr << "Invalid synchronization method. Exiting." << std::endl;
        return 1;
    }

    data->threadId = thread;
    threadObjects.push_back(thread);
}



     auto endTimeCreateThreads = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double> createThreadsDuration = endTimeCreateThreads - startTime;
        std::cout<<" Time"<<createThreadsDuration.count()<<std::endl;
    int choice;
    
    std::cin>>choice;
   

    do
    {
        std::cout << "\nThread Control Menu:" << std::endl;
        std::cout << "1. Set thread priority" << std::endl;
        std::cout << "2. Exit a thread" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "4. Display results" << std::endl;
        std::cout << "5. Detach a thread" << std::endl; 
        std::cout << "6. Cancel a thread" << std::endl; 
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        int threadNumber;
        std::cout << "Enter the thread number: ";
        std::cin >> threadNumber;
if (threadNumber >= 1 && threadNumber <= numProcesses)
        {
            ThreadData &selectedThreadData = threadDataObjects[threadNumber - 1];

switch (choice)
            {
            case 1:
                int newPriority;
                std::cout << "Enter the new priority: ";
                std::cin >> newPriority;
                setThreadPriority(&selectedThreadData, newPriority);
                break;
            case 2:
                pthread_cancel(selectedThreadData.threadId);
                exitThread(&selectedThreadData);
                pthread_join(selectedThreadData.threadId, NULL);
                break;
            case 3:
                // Exit the program
                break;
            case 4:
                displayResults();
                break;
            case 5:
            detach(threadObjects);
                 break;

            case 6:
                cancelThread(&selectedThreadData);
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                break; 
            }
        }

    } while (choice != 3);

   

    pthread_rwlock_destroy(&rwlock);
    pthread_cond_destroy(&cv);

    return 0;
}