#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <chrono>
#include <vector>
#include <cmath>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>

float function(float x) {
    return (x + x * x + x * x * x) / cos(x);
}

void tabulateFunction(int fd, float start, float end, float step) {
    char buffer[100];
    int n;

    n = sprintf(buffer, "\n|   ID  |    x    |      y     |\n");
    write(fd, buffer, n);
    

    for (float x = start; x < end; x += step) {
        n = sprintf(buffer, "| %5u | %.5f | % 10.5f |\n", getpid(), x, function(x));
        write(fd, buffer, n);
    }
}

int main() {
    float a = 0, b = 0, step = 0;
    size_t parallelProcessCount = 1;

    int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::cout << "Enter the bounds of tabulation: ";
    std::cin >> a >> b;
    std::cout << "Enter the step: ";
    std::cin >> step;
    std::cout << "Enter the number of parallel processes: ";
    std::cin >> parallelProcessCount;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<pid_t> children;

    for (size_t i = 0; i < parallelProcessCount; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "Fork failed\n";
            return 1;
        } else if (pid == 0) {
            // Child process
            float chunkSize = (b - a) / parallelProcessCount;
            float start = a + i * chunkSize;
            float end = start + chunkSize;
            tabulateFunction(fd, start, end, step);
            close(fd);
            return 0;
        } else {
            // Parent process
            children.push_back(pid);
        }
    }

    // Wait for all child processes to complete
    for (pid_t child : children) {
        waitpid(child, NULL, 0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    char buffer[100];
    int n;

    n = sprintf(buffer, "----------------------\n");
    write(fd, buffer, n);
    n = sprintf(buffer, "----------------------\n");
    write(fd, buffer, n);
    n = sprintf(buffer, "----------------------\n");
    write(fd, buffer, n);
    n = sprintf(buffer, "Time elapsed: %f seconds\n", duration.count());
    write(fd, buffer, n);
    n = sprintf(buffer, "----------------------\n");
    write(fd, buffer, n);
    n = sprintf(buffer, "----------------------\n");
    write(fd, buffer, n);
    n = sprintf(buffer, "----------------------\n");
    write(fd, buffer, n);

    fchmod(fd, 0444);

    close(fd);
    return 0;
}
