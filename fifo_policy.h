#ifndef FIFO_POLICY_H
#define FIFO_POLICY_H

#include "page_replacement_policy.h"
#include <queue>

class FIFOPolicy : public PageReplacementPolicy {
private:
    std::queue<int> fifoQueue;
public:
    int selectVictimFrame(int* pageFrames, int numFrames) override {
        int oldest = fifoQueue.front();
        fifoQueue.pop();
        return oldest;
    }
    void pageLoaded(int page) override {
        fifoQueue.push(page);
    }
};

#endif // FIFO_POLICY_H 