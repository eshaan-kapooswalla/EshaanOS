#include <iostream>
#include <string>

// Enum to represent process states
enum class ProcessState {
    READY = 0,
    RUNNING,
    SLEEPING,
    ZOMBIE
};

// Struct to represent a process
struct Process {
    int pid;                     // Process ID
    std::string name;            // Executable name
    int arrivalTime;             // Arrival time in the system
    int burstTime;               // Total CPU time required
    int priority;                // Lower value = higher priority
    ProcessState state;          // Current state of the process
    int memoryUsage;             // Memory in MB
    float cpuUsage;              // CPU usage in %

    // Constructor to initialize a process
    Process(int id, const std::string& n, int arrive, int burst, int prio)
        : pid(id), name(n), arrivalTime(arrive), burstTime(burst),
          priority(prio), state(ProcessState::READY), memoryUsage(0), cpuUsage(0.0f) {}
};

int main() {
    Process myProcess(1, "my_app", 0, 10, 2);

    std::cout << "PID: " << myProcess.pid << std::endl;
    std::cout << "Name: " << myProcess.name << std::endl;
    std::cout << "Arrival Time: " << myProcess.arrivalTime << std::endl;
    std::cout << "Burst Time: " << myProcess.burstTime << std::endl;
    std::cout << "Priority: " << myProcess.priority << std::endl;
    std::cout << "State: " << static_cast<int>(myProcess.state) << std::endl;
    std::cout << "Memory Usage: " << myProcess.memoryUsage << " MB" << std::endl;
    std::cout << "CPU Usage: " << myProcess.cpuUsage << "%" << std::endl;

    return 0;
} 