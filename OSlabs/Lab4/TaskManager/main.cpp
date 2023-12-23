#include <iostream>
#include <cstdio>
#include <chrono>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

struct process{
    pid_t pid = 0;
    std::string name;
    bool isRunning = true;
    bool isStopped = false;
    float executionTime = 0;
    int nice = 0;
};

void updateProcessInfo(process &p)
{
    int status = 0;
    int exitValue = waitpid(p.pid, &status, WNOHANG | WUNTRACED);
    if(exitValue == 0){
        p.isRunning = true;
    }else if (exitValue > 0){
        if(WIFSTOPPED(status)){
            p.isStopped = true;
        }else{
            p.isStopped = false;
        }
        if(WIFCONTINUED(status)){
            p.isStopped = false;
        }
        if(WIFEXITED(status) | WIFSIGNALED(status)){
            p.isRunning = false;
        }

    }else{
        p.isRunning = false;
        perror("waitpid");
    }

    rusage childUsage;
    if (getrusage(RUSAGE_CHILDREN, &childUsage) == 0) {
        p.executionTime = childUsage.ru_utime.tv_sec + (float)childUsage.ru_utime.tv_usec * 0.000001f;
    }else{
        perror("getrusage");
    }

    p.nice = getpriority(PRIO_PROCESS, p.pid);
};

int getCommand(std::string command, process &p){
    
    if (command == "pause") {
        kill(p.pid, SIGSTOP);
        return 1;
    }
    else if (command == "resume")
    {
        kill(p.pid, SIGCONT);
        return 1;
    }
    else if (command == "priority")
    {
        int newPriority = 0;
        std::cout << "\nEnter new priority(-20 to 19): ";
        std::cin >> newPriority;
        setpriority(PRIO_PROCESS, p.pid, newPriority);
        return 1;
    }
    else if (command == "kill")
    {
        kill(p.pid, SIGKILL);
        return 1;
    }
    else if (command == "setaffinity") {
        int cpuCores;
        std::cout << "\nEnter the number of CPU cores to use: ";
        std::cin >> cpuCores;
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        for (int i = 0; i < cpuCores; ++i)
        {
            CPU_SET(i, &cpuset);
        }
        sched_setaffinity(p.pid, sizeof(cpuset), &cpuset);
        return 1;
    }
    else if (command == "show")
    {
        return 1;
    }
    else if (command == "exit")
    {
        return 2;
    }
    else
    {
        return 0;

    }
}

void printProcessInfo(const process &p)
{
    std::string state;
    if (p.isRunning == true)
    {
        state = "Running";
    }
    else
    {
        state = "Killed";
    }
    if (p.isStopped == true)
        state = "Stopped";

    /*mvprintw(10, 10, "| %5u | %10s | %6s | % 3d |%6.3f |\n",
           p.pid, p.name.c_str(), state.c_str(),
           p.nice, p.executionTime);*/
    std::printf("| %5u | %10s | %6s | % 4d |%7.3f |\n",
           p.pid, p.name.c_str(), state.c_str(),
           p.nice, p.executionTime);
}

int main(){
    std::vector<process> childProcess;
    childProcess.push_back({0, "fibonacci"});
    childProcess.push_back({0, "tabulation"});

    pid_t pid = fork();
    if(pid == 0){
        //execlp("/bin/bash", "bash", "./fibonacci.sh",  NULL);
        execlp("/usr/bin/xterm", "xterm", "-e", "./fibonacci", NULL);
        perror("execlp");
    }
    childProcess[0].pid = pid;
    pid = fork();
    if(pid == 0){
        //execlp("/bin/bash", "bash", "./fibonacci.sh",  NULL);
        execlp("/usr/bin/xterm", "xterm", "-e", "./tabulation", NULL);
        //execlp("./fibonacci", childProcess[1].name.data(), NULL);
        perror("execlp");
    }
    childProcess[1].pid = pid;

    std::cout << childProcess[0].pid << '\n';
    std::cout << childProcess[1].pid << '\n';

    while(true){
        pid_t id;
        std::string command;
        std::cout << "Enter command and PID: ";
        std::cin >> command;
        std::cin >> id;
        if(getCommand(command, childProcess[id]) == 2)
            break;
        if(getCommand(command, childProcess[id]) == 1){
            std::printf("------------------------------------------------\n");
            std::printf("|  PID  |    Name    |  Status | Nice | U.Time |\n");
            for (size_t i = 0; i < childProcess.size(); i++)
            {
                updateProcessInfo(childProcess[i]);
                if (childProcess[i].isRunning == false)
                    childProcess.erase(childProcess.begin() + i);
                printProcessInfo(childProcess[i]);
            }
            std::printf("------------------------------------------------\n");
        }
        wait4(-1, NULL, WNOHANG, NULL);
    }
    return 0;
}