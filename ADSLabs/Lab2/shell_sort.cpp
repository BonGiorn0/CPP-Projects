#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

// Function to perform Shell sort on an array of pairs
void shellSort(std::vector<std::pair<float, int>>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            std::pair<float, int> temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap].first > temp.first; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
        /*std::cout << "Step: ";
        for (size_t i = 0; i < n; i++)
        {
            std::cout << arr[i].first << ' ';
        }
        std::cout << '\n';*/
        
    }

}

// Function to print the matrix
void printMatrix(const std::vector<std::vector<float>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n, m;

    // Get user input for the matrix dimensions
    std::cout << "Enter the number of rows (n): ";
    std::cin >> n;
    std::cout << "Enter the number of columns (m): ";
    std::cin >> m;

    // Create a 2D matrix
    std::vector<std::vector<float>> matrix(n, std::vector<float>(m));

    // Fill the matrix with random float numbers
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 100.0f;
        }
    }

    // Display the original matrix
    /*std::cout << "Original Matrix:" << std::endl;
    printMatrix(matrix);*/

    // Create a vector of pairs to store the values in the first row along with their original column indices
    std::vector<std::pair<float, int>> firstRowWithIndex;
    for (int j = 0; j < m; j++) {
        firstRowWithIndex.push_back({matrix[0][j], j});
    }

    // Measure the sorting time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Sort the vector of pairs based on the values in the first row using Shell sort
    shellSort(firstRowWithIndex);

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    // Rearrange the columns of the matrix based on the sorted indices
    std::vector<std::vector<float>> sortedMatrix(n, std::vector<float>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sortedMatrix[i][j] = matrix[i][firstRowWithIndex[j].second];
        }
    }

    // Display the matrix sorted by the values in the first row
    /*std::cout << "Matrix Sorted by First Row:" << std::endl;
    printMatrix(sortedMatrix);*/

    std::cout << "Sorting Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
