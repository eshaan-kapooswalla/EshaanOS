#include <iostream>
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
    int pid;
    std::string name;
    int priority;
    ProcessState state;
    Process(int id, std::string n, int prio)
        : pid(id), name(n), priority(prio), state(NEW) {}
};

std::vector<Process> processes;
int next_pid = 1;

void createProcess() {
    std::string name;
    int priority;
    std::cout << "Enter process name: ";
    std::cin >> name;
    std::cout << "Enter priority (1-10): ";
    while (!(std::cin >> priority) || priority < 1 || priority > 10) {
        std::cout << "Please enter a value between 1 and 10: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    processes.emplace_back(next_pid++, name, priority);
    std::cout << "Process '" << name << "' created with PID " << (next_pid-1) << "\n";
}

bool start_process(int pid, std::string& error_message) {
    for (auto& process : processes) {
        if (process.pid == pid) {
            if (process.state == NEW || process.state == PAUSED) {
                process.state = RUNNING;
                return true;
            } else {
                error_message = "Error: Process is already " + stateToString(process.state);
                return false;
            }
        }
    }
    error_message = "Error: Process with PID " + std::to_string(pid) + " not found";
    return false;
}

bool stop_process(int pid, std::string& error_message) {
    for (auto& process : processes) {
        if (process.pid == pid) {
            if (process.state == RUNNING) {
                process.state = STOPPED;
                return true;
            } else {
                error_message = "Error: Cannot stop a process that is " + stateToString(process.state);
                return false;
            }
        }
    }
    error_message = "Error: Process with PID " + std::to_string(pid) + " not found";
    return false;
}

bool pause_process(int pid, std::string& error_message) {
    for (auto& process : processes) {
        if (process.pid == pid) {
            if (process.state == RUNNING) {
                process.state = PAUSED;
                return true;
            } else {
                error_message = "Error: Cannot pause a process that is " + stateToString(process.state);
                return false;
            }
        }
    }
    error_message = "Error: Process with PID " + std::to_string(pid) + " not found";
    return false;
}

void listProcesses() {
    if (processes.empty()) {
        std::cout << "No processes created yet." << std::endl;
        return;
    }
    std::cout << "\nCurrent Processes:" << std::endl;
    for (const auto& p : processes) {
        std::cout << "PID: " << p.pid << ", Name: " << p.name
                  << ", Priority: " << p.priority << ", State: " << stateToString(p.state) << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "\nProcess Management CLI" << std::endl;
        std::cout << "1. Create Process" << std::endl;
        std::cout << "2. List Processes" << std::endl;
        std::cout << "3. Start Process" << std::endl;
        std::cout << "4. Pause Process" << std::endl;
        std::cout << "5. Stop Process" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }
        if (choice == 1) {
            createProcess();
        } else if (choice == 2) {
            listProcesses();
        } else if (choice == 3) {
            int pid;
            std::cout << "Enter PID to start: ";
            std::cin >> pid;
            std::string error;
            if (start_process(pid, error)) {
                std::cout << "Successfully started process with PID " << pid << std::endl;
            } else {
                std::cout << error << std::endl;
            }
        } else if (choice == 4) {
            int pid;
            std::cout << "Enter PID to pause: ";
            std::cin >> pid;
            std::string error;
            if (pause_process(pid, error)) {
                std::cout << "Successfully paused process with PID " << pid << std::endl;
            } else {
                std::cout << error << std::endl;
            }
        } else if (choice == 5) {
            int pid;
            std::cout << "Enter PID to stop: ";
            std::cin >> pid;
            std::string error;
            if (stop_process(pid, error)) {
                std::cout << "Successfully stopped process with PID " << pid << std::endl;
            } else {
                std::cout << error << std::endl;
            }
        } else if (choice == 6) {
            return 0;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
} 