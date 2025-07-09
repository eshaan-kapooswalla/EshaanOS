#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

enum ProcessState {
    NEW,
    RUNNING,
    PAUSED,
    STOPPED,
    COMPLETED
};

std::string stateToString(ProcessState state) {
    switch (state) {
        case NEW: return "NEW";
        case RUNNING: return "RUNNING";
        case PAUSED: return "PAUSED";
        case STOPPED: return "STOPPED";
        case COMPLETED: return "COMPLETED";
        default: return "UNKNOWN";
    }
}

struct Process {
    int id;
    std::string name;
    int arrivalTime;
    int burstTime;
    int priority;
    ProcessState state;
    Process(int id_, std::string n, int a, int b, int p, ProcessState s)
        : id(id_), name(n), arrivalTime(a), burstTime(b), priority(p), state(s) {}
};

std::vector<Process> processList = {
    {1, "App1", 0, 10, 5, RUNNING},
    {2, "App2", 2, 5, 3, PAUSED},
    {3, "App3", 1, 8, 4, STOPPED}
};

// Mock system state
int totalMemory = 1024; // MB
int freeMemory = 512;   // MB
std::string currentAlgorithm = "FCFS";

void viewProcesses() {
    using std::cout; using std::endl; using std::setw;
    cout << "\n--- Process List ---" << endl;
    cout << "| PID | Name   | State    | Arrival | Burst | Priority |" << endl;
    cout << "|-----|--------|----------|---------|-------|----------|" << endl;
    for (const auto& process : processList) {
        cout << "| " << setw(3) << process.id
             << " | " << setw(6) << process.name
             << " | " << setw(8) << stateToString(process.state)
             << " | " << setw(7) << process.arrivalTime
             << " | " << setw(5) << process.burstTime
             << " | " << setw(8) << process.priority
             << " |" << endl;
    }
}

void viewSystem() {
    using std::cout; using std::endl;
    int runningProcesses = 0;
    for (const auto& p : processList) {
        if (p.state == RUNNING) runningProcesses++;
    }
    cout << "\n--- System State ---" << endl;
    cout << "Total Memory: " << totalMemory << " MB" << endl;
    cout << "Free Memory: " << freeMemory << " MB" << endl;
    cout << "Scheduling Algorithm: " << currentAlgorithm << endl;
    cout << "Number of Running Processes: " << runningProcesses << endl;
}

void help() {
    std::cout << "\nAvailable Commands:" << std::endl;
    std::cout << "help            - Displays this help menu" << std::endl;
    std::cout << "view_processes  - Displays detailed process list" << std::endl;
    std::cout << "view_system     - Displays current system state" << std::endl;
    std::cout << "exit            - Exit the simulator" << std::endl;
}

int main() {
    std::string command;
    std::cout << "OS-Simulator> Type 'help' for available commands." << std::endl;
    while (true) {
        std::cout << "OS-Simulator> ";
        std::cin >> command;
        if (command == "help") {
            help();
        } else if (command == "view_processes") {
            viewProcesses();
        } else if (command == "view_system") {
            viewSystem();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
        }
    }
    return 0;
} 