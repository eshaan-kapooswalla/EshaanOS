#include <iostream>
#include <vector>
#include <string>

struct Process {
    std::string name;
    int arrivalTime;
    int burstTime;
    int priority;
    std::string state; // ready, running, waiting, terminated
    Process(std::string n, int aTime, int bTime, int prio)
        : name(n), arrivalTime(aTime), burstTime(bTime), priority(prio), state("ready") {}
};

std::vector<Process> processes;

void createProcess() {
    std::string name;
    int arrivalTime, burstTime, priority;
    std::cout << "Enter process name: ";
    std::cin >> name;
    std::cout << "Enter arrival time: ";
    while (!(std::cin >> arrivalTime) || arrivalTime < 0) {
        std::cout << "Please enter a valid non-negative integer: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cout << "Enter burst time: ";
    while (!(std::cin >> burstTime) || burstTime < 0) {
        std::cout << "Please enter a valid non-negative integer: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cout << "Enter priority (1-10): ";
    while (!(std::cin >> priority) || priority < 1 || priority > 10) {
        std::cout << "Please enter a value between 1 and 10: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    Process newProcess(name, arrivalTime, burstTime, priority);
    processes.push_back(newProcess);
    std::cout << "Process '" << name << "' created successfully!" << std::endl;
}

void listProcesses() {
    if (processes.empty()) {
        std::cout << "No processes created yet." << std::endl;
        return;
    }
    std::cout << "\nCurrent Processes:" << std::endl;
    for (const auto& p : processes) {
        std::cout << "Name: " << p.name << ", Arrival: " << p.arrivalTime
                  << ", Burst: " << p.burstTime << ", Priority: " << p.priority
                  << ", State: " << p.state << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "\nOperating System Simulator" << std::endl;
        std::cout << "1. Create Process" << std::endl;
        std::cout << "2. List Processes" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }
        switch (choice) {
            case 1:
                createProcess();
                break;
            case 2:
                listProcesses();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
} 