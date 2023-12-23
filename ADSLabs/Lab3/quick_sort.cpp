#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

// Custom quick sort function
void quickSort(std::vector<float>& arr, int left, int right) {
    if (left < right) {
        float pivot = arr[left];
        int i = left, j = right;

        while (i < j) {
            while (i < j && arr[j] >= pivot) {
                j--;
            }
            if (i < j) {
                arr[i++] = arr[j];
            }

            while (i < j && arr[i] <= pivot) {
                i++;
            }
            if (i < j) {
                arr[j--] = arr[i];
            }
        }

        arr[i] = pivot;

        // Print the vector at each iteration
        /*std::cout << "Iteration " << (left - right) / 2 << ": ";
        for (const float& num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;*/

        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Get the size of the vector from the user
    int vectorSize;
    std::cout << "Enter the size of the vector: ";
    std::cin >> vectorSize;

    // Generate a vector of random float numbers
    std::vector<float> numbers;
    for (int i = 0; i < vectorSize; i++) {
        float randomFloat = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        numbers.push_back(randomFloat);
    }

    /*std::cout << "Unsorted Vector:" << std::endl;
    for (const float& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/
    // Measure sorting time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Sort the vector using custom quick sort
    quickSort(numbers, 0, numbers.size() - 1);

    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration(endTime - startTime);

    float median;
    if (vectorSize % 2 == 0) {
        median = (numbers[vectorSize / 2 - 1] + numbers[vectorSize / 2]) / 2.0f;
    } else {
        median = numbers[vectorSize / 2];
    }

    numbers.erase(std::remove(numbers.begin(), numbers.end(), median), numbers.end());

    // Print the sorted vector
    /*std::cout << "Sorted Vector:" << std::endl;
    for (const float& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/

    std::cout << "Sorting time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
