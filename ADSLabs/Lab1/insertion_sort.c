#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>


int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    return static_cast<float>(rand() * fraction * (max - min + 1) + min);
}

void fill_array(float *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = getRandomNumber(-100, 100);
    }
    
}

bool less(float a, float b)
{
    return a < b;
}

bool isSorted(float *arr, size_t n, bool (*condition)(float, float))
{
    for (size_t i = 0; i < n - 1; i++)
    {
        if(!condition(arr[i], arr[i + 1]))
            return false;
    }
    return true;
}


void strange_function(float *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if(i % 2 == 0)
            arr[i] = sqrt(abs(arr[i] - 10));
    }
    

}

void insertion_sort(float *arr, size_t n, bool (*condition)(float, float))
{
    for (size_t i = 0; i < n; i++)
    {
        size_t replacePos = i;
        float curr = arr[i];
        for (size_t j = i; j > 0; j--)
        {
            if(!condition(curr, arr[j - 1]))
                break;
            arr[j] = arr[j - 1];
            replacePos = j - 1;
        }
        arr[replacePos] = curr;
        
    }
}

void selection_sort(float *arr, size_t n, bool (*condition)(float, float))
{
    for (size_t i = 0; i < n - 1; i++)
    {
        size_t currId = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if(condition(arr[j], arr[currId]))
                currId = j;
        }
        std::swap(arr[currId], arr[i]);
        //std::cout << "Step " << i << ": ";
        //for (size_t i = 0; i < n; i++)
        //{
        //    std::cout << arr[i] << ' ';
        //}
        //std::cout << '\n';
    }
}

int main()
{
    srand(time(NULL));
    size_t n;
    float *arr = nullptr;
    std::cout << "Enter a length of list: ";
    std::cin >> n;
    arr = new float[n];

    //std::cout << "Enter a list to sort: ";
    //for (size_t i = 0; i < n; i++)
    //{
    //    std::cin >> arr[i];
    //}
    fill_array(arr, n);
    strange_function(arr, n);
    /*std::cout << "The unsorted list: ";
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }*/
    std::cout << '\n';
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    selection_sort(arr, n, less);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - begin;

    std::cout << "Sort duration = " << 
        duration.count() << " seconds\n";

    /*std::cout << "The sorted list: ";
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    std::cout << "Array is ";
    if(isSorted(arr, n, less))
        std::cout << "sorted\n";
    else
        std::cout << "not sorted\n";
*/

    delete [] arr;
    
    return 0;
}