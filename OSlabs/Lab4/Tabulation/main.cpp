#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ncurses.h>
#include <cmath>
#include <chrono>
#include <vector>

float function(float x)
{
	return (x + x*x + x*x*x) / cos(x);
}

void tabulateFunction(FILE *f, float a, float step, size_t iterationCount)
{
	for (size_t i = 0; i < iterationCount; i++) {
		//std::cout << "| " << i << " | " << a << " | " << function(a) << " |\n";
		fprintf(f, "| %5u | %.5f | % 10.5f |\n", getpid(), a, function(a));
		a += step;
	}
}


int main(){
    float a = 0, b = 0, step = 0;
	size_t parallelProcessCount = 1;
	size_t originalCmdLineSize = 0;
    FILE *f;
    f = fopen("out.txt", "w");

	std::cout << "Enter the bounds of tabulation: ";
	std::cin >> a >> b;
	std::cout << "Enter the step: ";
	std::cin >> step;
	std::cout << "Enter the number of parallel processes: ";
	std::cin >> parallelProcessCount;

	size_t commandArgIterationCount = (size_t)(round((b - a) / step / parallelProcessCount));
    std::vector<pid_t> children;
    children.reserve(commandArgIterationCount);

	fprintf(f, "\n|   ID  |    x    |      y     |\n");
    fflush(f);
	auto start = std::chrono::system_clock::now();
    pid_t pid = fork();
    children.push_back(pid);
	for (size_t i = 0; i < parallelProcessCount; i++)
	{
        if (pid == 0)
        {
            tabulateFunction(f, a, step, commandArgIterationCount);
            return 0;
            
        }
        else if(pid > 0)
        {
            a += commandArgIterationCount * step;
            pid = fork();
            children.push_back(pid);
        }
        else
        {

        }
        //wait(NULL);

	}
    //auto end = std::chrono::system_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    //if(pid > 0)
    //    fprintf(stdout, "%u\n", elapsed.count());
    
    if(pid > 0){
        for (size_t i = 0; i < parallelProcessCount; i++)
                waitpid(children[i], NULL, 0);
        //bool childrenAreRunning = true;
        //while (childrenAreRunning)
        //{
        //    bool allDone = false;
        //    for (size_t i = 0; i < parallelProcessCount; i++)
        //        allDone |= !waitpid(children[i], NULL, 0);
        //    childrenAreRunning &= allDone;
        //}
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = end - start;


        fprintf(f, "----------------------\n");
        fprintf(f, "----------------------\n");
        fprintf(f, "----------------------\n");
        fprintf(stdout, "Time elapsed(): %f\n", duration.count());
        fprintf(f, "----------------------\n");
        fprintf(f, "----------------------\n");
        fprintf(f, "----------------------\n");
    }
    return 0;
}