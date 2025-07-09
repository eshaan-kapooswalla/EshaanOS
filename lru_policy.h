#ifndef LRU_POLICY_H
#define LRU_POLICY_H

#include "page_replacement_policy.h"
#include <unordered_map>
#include <climits>

class LRUPolicy : public PageReplacementPolicy {
private:
    std::unordered_map<int, int> pageUsage;
    int usageCounter = 0;
public:
    int selectVictimFrame(int* pageFrames, int numFrames) override {
        int victim = -1;
        int minCount = INT_MAX;
        for (int i = 0; i < numFrames; i++) {
            if (pageFrames[i] != -1 && pageUsage[pageFrames[i]] < minCount) {
                minCount = pageUsage[pageFrames[i]];
                victim = pageFrames[i];
            }
        }
        if (victim != -1) {
            pageUsage.erase(victim);
        }
        return victim;
    }
    void pageLoaded(int page) override {
        pageUsage[page] = usageCounter++;
    }
    void pageAccessed(int page) override {
        if (pageUsage.find(page) != pageUsage.end()) {
            pageUsage[page] = usageCounter++;
        }
    }
};

#endif // LRU_POLICY_H 