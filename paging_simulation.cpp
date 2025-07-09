#include <iostream>
#include <cstdio>

// Represents a page table entry
struct PageTableEntry {
    bool present = false;      // Indicates if the page is in physical memory
    bool modified = false;     // Indicates if the page has been modified
    bool read = true;          // Read permission
    bool write = true;         // Write permission
    int frameNumber = -1;      // The physical frame number this page is mapped to
};

// Represents a page table
struct PageTable {
    PageTableEntry* entries;
    int size;
};

// Represents a physical frame
struct Frame {
    bool isFree = true;   // Indicates if the frame is free
    int page = -1;        // The virtual page number mapped to this frame
};

// Simulate physical memory as an array of frames
Frame* physicalMemory = nullptr;
int totalFrames = 0;

// Initialize physical memory
void initializeMemory(int frames) {
    totalFrames = frames;
    physicalMemory = new Frame[frames];
    for (int i = 0; i < frames; i++) {
        physicalMemory[i].isFree = true;
        physicalMemory[i].page = -1;
    }
}

// FIFO page replacement algorithm
int findFrameToReplace() {
    static int lastReplaced = 0;
    int frameToReplace = lastReplaced;
    lastReplaced = (lastReplaced + 1) % totalFrames;
    return frameToReplace;
}

// Handle a page fault by loading the page into physical memory
void handlePageFault(PageTable& pageTable, int virtualPage) {
    // Find a frame to replace
    int frameNumber = findFrameToReplace();
    // If the frame is occupied, mark the old page as not present
    if (!physicalMemory[frameNumber].isFree) {
        int oldPage = physicalMemory[frameNumber].page;
        pageTable.entries[oldPage].present = false;
        pageTable.entries[oldPage].frameNumber = -1;
    }
    // Update the page table
    PageTableEntry* entry = &pageTable.entries[virtualPage];
    entry->present = true;
    entry->frameNumber = frameNumber;
    // Update the frame information
    physicalMemory[frameNumber].isFree = false;
    physicalMemory[frameNumber].page = virtualPage;
    std::cout << "Page fault: Loaded virtual page " << virtualPage << " into frame " << frameNumber << std::endl;
}

int main() {
    // Initialize physical memory with 4 frames
    initializeMemory(4);
    // Create a sample page table with 8 pages
    PageTable pageTable;
    pageTable.size = 8;
    pageTable.entries = new PageTableEntry[8];
    // Initialize all page table entries as not present
    for (int i = 0; i < 8; i++) {
        pageTable.entries[i].present = false;
        pageTable.entries[i].frameNumber = -1;
    }
    int pageSize = 4096; // 4KB page size
    // Simulate accessing a sequence of virtual addresses
    int virtualAddresses[] = {0x1000, 0x2000, 0x3000, 0x4000, 0x1000, 0x5000, 0x6000, 0x7000, 0x8000, 0x1000};
    int numAccesses = sizeof(virtualAddresses) / sizeof(virtualAddresses[0]);
    for (int i = 0; i < numAccesses; ++i) {
        int virtualAddress = virtualAddresses[i];
        int virtualPage = virtualAddress / pageSize;
        int offset = virtualAddress % pageSize;
        // Check if the page is present
        if (!pageTable.entries[virtualPage].present) {
            handlePageFault(pageTable, virtualPage);
        }
        // Now access the frame
        int frameNumber = pageTable.entries[virtualPage].frameNumber;
        int physicalAddress = frameNumber * pageSize + offset;
        printf("Virtual Address 0x%x maps to Physical Address 0x%x\n", virtualAddress, physicalAddress);
    }
    // Clean up
    delete[] pageTable.entries;
    delete[] physicalMemory;
    return 0;
} 