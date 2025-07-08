#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "scheduler.h"

class FCFScheduler : public Scheduler {
public:
    void schedule(std::queue<Process>& processes) override;
};

#endif // FCFS_SCHEDULER_H 