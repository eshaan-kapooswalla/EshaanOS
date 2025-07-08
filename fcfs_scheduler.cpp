#include "fcfs_scheduler.h"
#include <iostream>

void FCFScheduler::schedule(std::queue<Process>& processes) {
    int currentTime = 0;
    std::cout << "FCFS Scheduling Algorithm" << std::endl;
    std::cout << "-------------------------" << std::endl;
    while (!processes.empty()) {
        Process& process = processes.front();
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }
        process.waitingTime = currentTime - process.arrivalTime;
        process.turnaroundTime = process.waitingTime + process.burstTime;
        process.completionTime = currentTime + process.burstTime;
        std::cout << "Process ID: " << process.id << std::endl;
        std::cout << "Name: " << process.name << std::endl;
        std::cout << "Arrival Time: " << process.arrivalTime << std::endl;
        std::cout << "Burst Time: " << process.burstTime << std::endl;
        std::cout << "Waiting Time: " << process.waitingTime << std::endl;
        std::cout << "Turnaround Time: " << process.turnaroundTime << std::endl;
        std::cout << "Started at: " << currentTime << " | Completed at: " << process.completionTime << std::endl;
        std::cout << "-------------------------" << std::endl;
        currentTime += process.burstTime;
        processes.pop();
    }
} 