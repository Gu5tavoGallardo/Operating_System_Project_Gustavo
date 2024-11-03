#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <iostream>
#include <queue>

class Process{
    public:
    int id;
    int cycles;

    Process(int id, int cycles);

};

class Scheduler{
    public:
    std::queue<Process> sjfQueue;
    std::queue<Process> fcfsQueue;

    void addProcess(Process process);

    void run();

    
};

#endif