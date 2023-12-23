#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

// Counting Sort function
void countingSort(std::vector<long>& arr) {
    long maxElement = *std::max_element(arr.begin(), arr.end());
    long minElement = *std::min_element(arr.begin(), arr.end());
    long range = maxElement - minElement + 1;

    std::vector<long> count(range);
    std::vector<long> output(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - minElement]++;
    }

    /*for (int i = 0; i < range; i++) {
        std::cout << count[i];
    }
    std::cout << '\n';*/

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minElement] - 1] = arr[i];
        count[arr[i] - minElement]--;
    }

    /*for (int i = 0; i < range; i++) {
        std::cout << count[i];
    }
    std::cout << '\n';*/

    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Get the size of the vector from the user
    long vectorSize;
    std::cout << "Enter the size of the vector: ";
    std::cin >> vectorSize;

    // Generate a vector of random integers within a specified range
    std::vector<long> numbers;
    long minRange = -1000000;  // Minimum range value
    long maxRange = 1000000;   // Maximum range value

    for (int i = 0; i < vectorSize; i++) {
        long randomInt = std::rand() % (maxRange - minRange + 1) + minRange;
        numbers.push_back(randomInt);
    }
    /*for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << ' ';
    }
    std::cout << '\n';*/

    /*for (int i = 0; i < vectorSize; i++) {
        numbers[i] *= numbers[i];
    }*/

    /*for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << ' ';
    }
    std::cout << '\n';*/
    // Measure sorting time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Counting Sort the vector
    countingSort(numbers);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(endTime - startTime);

    // Print the sorted vector
    /*std::cout << "Sorted Vector:" << std::endl;
    for (const int& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/

    std::cout << "Sorting time: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
