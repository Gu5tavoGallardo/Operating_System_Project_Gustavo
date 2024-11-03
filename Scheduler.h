#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <queue>

class Process {
public:
    int id;
    int cycles;

    // Constructor to initialize a Process with an ID and cycle count
    Process(int id, int cycles) : id(id), cycles(cycles) {}
};

class Scheduler {
public:
    // Queues for SJF and FCFS scheduling
    std::queue<Process> sjfQueue;
    std::queue<Process> fcfsQueue;

    // Method to add a process to the appropriate queue based on cycle count
    void addProcess(Process process) {
        if (process.cycles <= 50) {
            sjfQueue.push(process);
            std::cout << "Process " << process.id << " added to SJF queue with " << process.cycles << " cycles.\n";
        } else {
            fcfsQueue.push(process);
            std::cout << "Process " << process.id << " added to FCFS queue with " << process.cycles << " cycles.\n";
        }
    }

    // Method to execute the scheduling logic
    void run() {
        std::cout << "Running scheduler...\n";
        // Add your scheduling logic here
        // For example, alternate between sjfQueue and fcfsQueue
    }
};

#endif // SCHEDULER_H
