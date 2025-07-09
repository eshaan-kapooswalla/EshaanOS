#ifndef MEMORY_MANAGEMENT_STRUCTS_H
#define MEMORY_MANAGEMENT_STRUCTS_H

// Constants for simulation
const int VIRTUAL_PAGES = 1024;   // Number of virtual pages supported
const int PHYSICAL_FRAMES = 256;  // Number of physical frames available
const int TLB_SIZE = 32;          // Number of entries in the TLB

// Page Table Entry
struct PageTableEntry {
    int frame_number;      // Physical frame where the page is loaded
    bool present;          // Whether the page is in physical memory
    bool modified;         // Dirty bit
    bool referenced;       // Reference bit for page replacement algorithms
};

// Page Table
struct PageTable {
    PageTableEntry entries[VIRTUAL_PAGES];
};

// Frame in physical memory
struct Frame {
    int frame_number;      // Unique identifier for the frame
    int page;              // Virtual page number loaded into this frame
    int process_id;        // Process that owns this page
    int last_used;         // Timestamp for last access (for LRU, etc.)
};

// Physical Memory
struct PhysicalMemory {
    Frame frames[PHYSICAL_FRAMES];
};

// TLB Entry
struct TLBEntry {
    int virtual_page;
    int frame_number;
    int timestamp;         // When this entry was last used
};

// Translation Lookaside Buffer (TLB)
struct TranslationBuffer {
    TLBEntry entries[TLB_SIZE];
};

#endif // MEMORY_MANAGEMENT_STRUCTS_H 