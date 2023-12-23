#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <chrono>

// Merge function for merge sort
void merge(std::vector<float>& arr, int left, int middle, int right) {
    static int step = 1;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<float> leftArr(n1);
    std::vector<float> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] >= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
    /*std::cout << "Step" << step << ": ";
    for (const float& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    step++;*/
}

// Merge Sort function
void mergeSort(std::vector<float>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Get the size of the vector from the user
    int vectorSize;
    std::cout << "Enter the size of the vector: ";
    std::cin >> vectorSize;

    // Generate a vector of random float numbers between 0 and 100
    std::vector<float> numbers;
    for (int i = 0; i < vectorSize; i++) {
        float randomFloat = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        // Scale the random number to the range [-100, 100]
        randomFloat = randomFloat * 200.0f - 100;
        numbers.push_back(randomFloat);
    }
    
    for (float& num : numbers) {
        if (num < 0) {
            num = std::sin(num);
        }
    }


    /*std::cout << "Unsorted Vector:" << std::endl;
    for (const float& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/

    // Measure sorting time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Merge Sort the vector
    mergeSort(numbers, 0, numbers.size() - 1);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(endTime - startTime);

    // Apply sin function to negative elements
    // Print the modified vector
    /*std::cout << "Modified Vector:" << std::endl;
    for (const float& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/

    std::cout << "Sorting time: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
