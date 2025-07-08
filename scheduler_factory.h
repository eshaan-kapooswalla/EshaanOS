#ifndef SCHEDULER_FACTORY_H
#define SCHEDULER_FACTORY_H

#include "scheduler.h"
#include "fcfs_scheduler.h"
#include "sjf_scheduler.h"
#include "scheduler_type.h"

class SchedulerFactory {
public:
    static Scheduler* createScheduler(SchedulerType type) {
        switch(type) {
            case SchedulerType::FCFS:
                return new FCFScheduler();
            case SchedulerType::SJF:
                return new SJFScheduler();
            default:
                return nullptr;
        }
    }
};

#endif // SCHEDULER_FACTORY_H 