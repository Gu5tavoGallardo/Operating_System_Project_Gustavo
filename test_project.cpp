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
        cout << "Running scheduler...\n";
        // Add your scheduling logic here
        // For example, alternate between sjfQueue and fcfsQueue
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
