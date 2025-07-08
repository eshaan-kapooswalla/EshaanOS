#ifndef PROCESS_H
#define PROCESS_H

#include <string>

struct Process {
    int id;
    std::string name;
    int arrivalTime;
    int burstTime;
    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;
    // Add more fields as needed
    Process(int id_, const std::string& name_, int arrival, int burst)
        : id(id_), name(name_), arrivalTime(arrival), burstTime(burst) {}
};

#endif // PROCESS_H 