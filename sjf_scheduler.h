#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "scheduler.h"

class SJFScheduler : public Scheduler {
public:
    void schedule(std::queue<Process>& processes) override;
};

#endif // SJF_SCHEDULER_H 