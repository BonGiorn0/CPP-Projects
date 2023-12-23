#include <iostream>

int main() {
    int n;  // Number of Fibonacci numbers to print
    std::cout << "Enter the number of Fibonacci numbers to print: ";
    std::cin >> n;

    // Check if n is non-negative
    if (n < 0) {
        std::cout << "Please enter a non-negative number." << std::endl;
        return 1;  // Exit with an error code
    }

    if (n == 0) {
        std::cout << "No Fibonacci numbers to print." << std::endl;
    }
    else if (n == 1) {
        std::cout << "Fibonacci sequence:" << std::endl;
        std::cout << "0" << std::endl;
    }
    else {
        std::cout << "Fibonacci sequence:" << std::endl;
        int a = 0, b = 1;
        std::cout << a << " " << b << " ";  // Print the first two Fibonacci numbers

        for (int i = 2; i < n; i++) {
            int next = a + b;
            std::cout << next << " ";
            a = b;
            b = next;
        }
        std::cout << std::endl;
    }

    return 0;  // Exit normally
}
