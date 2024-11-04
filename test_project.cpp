#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

// Define the Process class
class Process {
public:
    int id;
    int cycles;

    // Constructor to initialize a Process with an ID and cycle count
    Process(int id, int cycles) : id(id), cycles(cycles) {}
};

// Define the Scheduler class
class Scheduler {
public:
    // Queues for SJF and FCFS scheduling
    queue<Process> sjfQueue;
    queue<Process> fcfsQueue;

    // Method to add a process to the appropriate queue based on cycle count
    void addProcess(Process process) {
        if (process.cycles <= 50) {
            sjfQueue.push(process);
            cout << "Process " << process.id << " added to SJF queue with " << process.cycles << " cycles.\n";
        } else {
            fcfsQueue.push(process);
            cout << "Process " << process.id << " added to FCFS queue with " << process.cycles << " cycles.\n";
        }
    }

    // Method to execute the scheduling logic
    void run() {
    const int SJF_CYCLE_LIMIT = 100;
    const int FCFS_CYCLE_LIMIT = 200;
    const int SJF_QUANTUM = 20;  // Time slice for each SJF process
    const int FCFS_QUANTUM = 50; // Time slice for each FCFS process

    int sjfCycleCount = 0;
    int fcfsCycleCount = 0;

    std::cout << "Starting refined scheduling...\n";

    while (!sjfQueue.empty() || !fcfsQueue.empty()) {
        // Process the SJF Queue with time-slicing
        while (!sjfQueue.empty() && sjfCycleCount < SJF_CYCLE_LIMIT) {
            Process process = sjfQueue.front();
            sjfQueue.pop();

            int allocateCycles = std::min(process.cycles, SJF_QUANTUM); // Allocate quantum or remaining cycles
            process.cycles -= allocateCycles;
            sjfCycleCount += allocateCycles;

            std::cout << "Executing SJF Process " << process.id 
                      << " for " << allocateCycles << " cycles. Remaining cycles: " 
                      << process.cycles << std::endl;

            if (process.cycles > 0) {
                sjfQueue.push(process);  // Re-add to queue if not finished
            }
        }

        // Reset SJF counter and switch to FCFS if cycle limit reached
        if (sjfCycleCount >= SJF_CYCLE_LIMIT || sjfQueue.empty()) {
            sjfCycleCount = 0;

            // Process the FCFS Queue with time-slicing
            while (!fcfsQueue.empty() && fcfsCycleCount < FCFS_CYCLE_LIMIT) {
                Process process = fcfsQueue.front();
                fcfsQueue.pop();

                int allocateCycles = std::min(process.cycles, FCFS_QUANTUM); // Allocate quantum or remaining cycles
                process.cycles -= allocateCycles;
                fcfsCycleCount += allocateCycles;

                std::cout << "Executing FCFS Process " << process.id 
                          << " for " << allocateCycles << " cycles. Remaining cycles: " 
                          << process.cycles << std::endl;

                if (process.cycles > 0) {
                    fcfsQueue.push(process);  // Re-add to queue if not finished
                }
            }

            // Reset FCFS counter if limit reached
            if (fcfsCycleCount >= FCFS_CYCLE_LIMIT || fcfsQueue.empty()) {
                fcfsCycleCount = 0;
            }
        }
    }

    std::cout << "All processes completed." << std::endl;
}



};

// Function to simulate the booting sequence
void bootingSystem() {
    cout << "Welcome to the Gus and Sophia Operating System" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Starting boot sequence..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Checking hardware..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Locating the bootloader..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Loading the Operating System..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Initializing the kernel..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Calling system services..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

// Function to handle admin login
bool loginSystem() {
    string username, password;
    const string adminUsername = "G@dm1n";
    const string adminPassword = "Gu5Th3bu5";

    cout << "Admin Username: ";
    cin >> username;

    cout << "Admin Password: ";
    cin >> password;

    return (username == adminUsername && password == adminPassword);
}

int main() {
    srand(time(0)); // Seed the random number generator

    bootingSystem();  // Run the booting sequence

    if (!loginSystem()) {
        cout << "Login failed. The Operating System will turn off now." << endl;
        return 1;
    }
    cout << "Login successful. Welcome!" << endl;

    Scheduler scheduler;  // Create a Scheduler instance
    char choice;
    int processId = 1; // Initialize process ID counter

    // Loop for process creation
    while (true) {
        cout << "Do you want to create a new process? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            int randomCycles = rand() % 191 + 10; // Generate random cycles between 10 and 200
            Process newProcess(processId++, randomCycles); // Create a new Process object
            scheduler.addProcess(newProcess);  // Add the new process to the scheduler
        } else if (choice == 'n' || choice == 'N') {
            cout << "No more processes to create. Starting the scheduler...\n";
            break;
        } else {
            cout << "Invalid choice! Please enter 'y' or 'n'.\n";
        }
    }

    scheduler.run();  // Run the scheduling logic
    return 0;
}
