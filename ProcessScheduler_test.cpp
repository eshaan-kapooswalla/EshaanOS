#include <iostream>
#include <queue>
#include "scheduler_factory.h"
#include "process.h"

void testFCFS() {
    std::queue<Process> processes;
    processes.push(Process(1, "P1", 0, 5));
    processes.push(Process(2, "P2", 2, 3));
    processes.push(Process(3, "P3", 4, 1));

    Scheduler* scheduler = SchedulerFactory::createScheduler(SchedulerType::FCFS);
    std::cout << "\n=== FCFS Test Case ===\n";
    scheduler->schedule(processes);
    delete scheduler;
}

void testSJF() {
    std::queue<Process> processes;
    processes.push(Process(4, "P4", 0, 4));
    processes.push(Process(5, "P5", 1, 2));
    processes.push(Process(6, "P6", 3, 1));

    Scheduler* scheduler = SchedulerFactory::createScheduler(SchedulerType::SJF);
    std::cout << "\n=== SJF Test Case ===\n";
    scheduler->schedule(processes);
    delete scheduler;
}

int main() {
    testFCFS();
    testSJF();
    return 0;
} 