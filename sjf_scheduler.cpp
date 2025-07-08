#include "sjf_scheduler.h"
#include <iostream>
#include <vector>
#include <queue>

void SJFScheduler::schedule(std::queue<Process>& processes) {
    int currentTime = 0;
    std::vector<Process> readyQueue;
    std::vector<Process> allProcesses;
    // Move all processes from queue to vector for easier management
    while (!processes.empty()) {
        allProcesses.push_back(processes.front());
        processes.pop();
    }
    int completed = 0;
    int n = allProcesses.size();
    std::vector<bool> isDone(n, false);
    std::cout << "SJF Scheduling Algorithm" << std::endl;
    std::cout << "-------------------------" << std::endl;
    while (completed < n) {
        int idx = -1;
        int minBurst = INT32_MAX;
        for (int i = 0; i < n; ++i) {
            if (!isDone[i] && allProcesses[i].arrivalTime <= currentTime) {
                if (allProcesses[i].burstTime < minBurst) {
                    minBurst = allProcesses[i].burstTime;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        Process& process = allProcesses[idx];
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
        isDone[idx] = true;
        completed++;
    }
} 