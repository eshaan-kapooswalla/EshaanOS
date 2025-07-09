#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "page_table.h"
#include "physical_memory.h"
#include "page_replacement_policy.h"

class MemoryManager {
private:
    PageTable* pageTable;
    PhysicalMemory* physicalMemory;
    PageReplacementPolicy* replacementPolicy;
public:
    MemoryManager(PageTable* pt, PhysicalMemory* pm, PageReplacementPolicy* policy)
        : pageTable(pt), physicalMemory(pm), replacementPolicy(policy) {}
    int handlePageFault(int virtualPage) {
        int physicalFrame = pageTable->getPhysicalFrame(virtualPage);
        if (physicalFrame == -1) {
            physicalFrame = findFreeFrame();
            if (physicalFrame == -1) {
                int victimPage = replacementPolicy->selectVictimFrame(physicalMemory->getFrames(), physicalMemory->getNumFrames());
                int victimFrame = pageTable->getPhysicalFrame(victimPage);
                pageTable->unmapPage(victimPage);
                physicalMemory->unloadPage(victimFrame);
                physicalFrame = victimFrame;
            }
            pageTable->mapPage(virtualPage, physicalFrame);
            physicalMemory->loadPage(physicalFrame, virtualPage);
            replacementPolicy->pageLoaded(virtualPage);
            return physicalFrame;
        }
        return physicalFrame;
    }
private:
    int findFreeFrame() {
        int* frames = physicalMemory->getFrames();
        for (int i = 0; i < physicalMemory->getNumFrames(); i++) {
            if (frames[i] == -1) {
                return i;
            }
        }
        return -1;
    }
};

#endif // MEMORY_MANAGER_H 