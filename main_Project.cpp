#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <Scheduler.h> 
using namespace std;

void bootingSystem() {
    cout << "Welcome to the Gustavo's Operating System" << endl;
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

bool loginSystem() {
    string username, password;
    const string adminUsername = "G@dm1n";
    const string adminPassword = "Gu5Th3bu5";

    cout << "Admin Username: ";
    cin >> username;

    cout << "Admin Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        return true;
    } else {
        return false;
    }
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
            int randomCycles = rand() % 191 + 10; // Random cycles between 10 and 200
            Process newProcess(processId++, randomCycles); // Create a new Process
            scheduler.addProcess(newProcess);  // Add it to the scheduler
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