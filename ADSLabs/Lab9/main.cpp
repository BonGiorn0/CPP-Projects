#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>  
#include <ctime>

int iter = 0;

int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        ++iter;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1; 
            std::cout << "\nПошук в:\n";
            for (int i = left; i <= right; i++)
            {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
        else {
            right = mid - 1; 
            std::cout << "\nПошук в:\n";
            for (int i = left; i <= right; i++)
            {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    return -1; 
}

int main()
{
    setlocale(LC_CTYPE, "ukr");
    int n;
    std::cout << "Введiть розмiр масиву: ";
    std::cin >> n;

    std::vector<int> A(n);

    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < n; ++i) {
        A[i] = rand() % 100; 
    }

    std::cout << "\nМасив перед операцiями:\n";
    for (int elem : A) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;


    std::sort(A.begin(), A.end());
    auto maxIt = std::max_element(A.begin(), A.end());

    std::cout << "\nМасив після сортування:\n";
    for (int elem : A) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    int k = *maxIt - 5;
    int result = binarySearch(A, k);

    if (result != -1) {
        std::cout << "\nЕлемент " << k << " знайдено пiд iндексом " << result << ".\n";
    }
    else {
        std::cout << "\nЕлемент " << k << " не знайдено в масивi.\n";
    }

    std::cout << "\nКiлькiсть порiвнянь: " << iter << std::endl;
}