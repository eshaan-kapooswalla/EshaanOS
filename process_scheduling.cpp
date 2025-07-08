#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority; // For future use
};

struct Metrics {
    int waitingTime;
    int turnaroundTime;
};

void implementFCFS(const std::vector<Process>& processes) {
    std::vector<Metrics> metrics(processes.size());
    int currentTime = 0;
    int totalWaiting = 0, totalTurnaround = 0;
    std::cout << "Execution Order (FCFS):\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        const Process& p = processes[i];
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        metrics[i].waitingTime = currentTime - p.arrivalTime;
        metrics[i].turnaroundTime = metrics[i].waitingTime + p.burstTime;
        totalWaiting += metrics[i].waitingTime;
        totalTurnaround += metrics[i].turnaroundTime;
        std::cout << "Time " << currentTime << ": Process " << p.id << " starts (Arrival: " << p.arrivalTime << ", Burst: " << p.burstTime << ")\n";
        currentTime += p.burstTime;
        std::cout << "Time " << currentTime << ": Process " << p.id << " finishes\n";
    }
    std::cout << "\nProcess\tWaiting\tTurnaround\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id << "\t" << metrics[i].waitingTime << "\t" << metrics[i].turnaroundTime << "\n";
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << (double)totalWaiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (double)totalTurnaround / processes.size() << "\n";
}

void implementSJF(const std::vector<Process>& processes) {
    struct ProcWithIndex {
        Process p;
        size_t originalIndex;
        bool completed = false;
    };
    std::vector<ProcWithIndex> procList;
    for (size_t i = 0; i < processes.size(); ++i) {
        procList.push_back({processes[i], i, false});
    }
    std::vector<Metrics> metrics(processes.size());
    int currentTime = 0;
    int completedCount = 0;
    int totalWaiting = 0, totalTurnaround = 0;
    std::cout << "Execution Order (SJF):\n";
    while (completedCount < (int)processes.size()) {
        int idx = -1;
        int minBurst = INT32_MAX;
        for (size_t i = 0; i < procList.size(); ++i) {
            if (!procList[i].completed && procList[i].p.arrivalTime <= currentTime) {
                if (procList[i].p.burstTime < minBurst) {
                    minBurst = procList[i].p.burstTime;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            // No process has arrived yet
            currentTime++;
            continue;
        }
        ProcWithIndex& chosen = procList[idx];
        metrics[chosen.originalIndex].waitingTime = currentTime - chosen.p.arrivalTime;
        metrics[chosen.originalIndex].turnaroundTime = metrics[chosen.originalIndex].waitingTime + chosen.p.burstTime;
        totalWaiting += metrics[chosen.originalIndex].waitingTime;
        totalTurnaround += metrics[chosen.originalIndex].turnaroundTime;
        std::cout << "Time " << currentTime << ": Process " << chosen.p.id << " starts (Arrival: " << chosen.p.arrivalTime << ", Burst: " << chosen.p.burstTime << ")\n";
        currentTime += chosen.p.burstTime;
        std::cout << "Time " << currentTime << ": Process " << chosen.p.id << " finishes\n";
        chosen.completed = true;
        completedCount++;
    }
    std::cout << "\nProcess\tWaiting\tTurnaround\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id << "\t" << metrics[i].waitingTime << "\t" << metrics[i].turnaroundTime << "\n";
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << (double)totalWaiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (double)totalTurnaround / processes.size() << "\n";
}

int main() {
    std::vector<Process> processes = {
        {1, 0, 10, 1},
        {2, 1, 5, 2},
        {3, 2, 8, 3},
        {4, 3, 3, 4}
    };

    std::cout << "FCFS Scheduling:\n";
    implementFCFS(processes);

    std::cout << "\nSJF Scheduling:\n";
    implementSJF(processes);

    return 0;
} 