#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include "process.h"

class Scheduler {
public:
    virtual ~Scheduler() {}
    virtual void schedule(std::queue<Process>& processes) = 0;
};

#endif // SCHEDULER_H 