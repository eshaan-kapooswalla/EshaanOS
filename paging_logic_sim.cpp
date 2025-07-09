#include <iostream>
#include <queue>
#include <map>

const int PAGE_SIZE = 4096; // 4KB
const int NUM_FRAMES = 4;   // Number of physical frames

std::queue<int> free_frames; // Available physical frames
std::queue<int> frame_queue; // For FIFO replacement
std::map<int, int> mapped_pages; // virtual_page -> physical_frame

// Function to map a virtual page to a physical frame
int map_virtual_to_physical(int virtual_page) {
    // Check if the page is already mapped
    if (mapped_pages.find(virtual_page) != mapped_pages.end()) {
        return mapped_pages[virtual_page];
    }
    // If there are free frames, use one
    if (!free_frames.empty()) {
        int physical_frame = free_frames.front();
        free_frames.pop();
        mapped_pages[virtual_page] = physical_frame;
        frame_queue.push(virtual_page);
        std::cout << "Page fault: Loaded virtual page " << virtual_page << " into frame " << physical_frame << std::endl;
        return physical_frame;
    }
    // If no free frames, replace using FIFO policy
    int victim_page = frame_queue.front();
    frame_queue.pop();
    int victim_frame = mapped_pages[victim_page];
    mapped_pages.erase(victim_page);
    mapped_pages[virtual_page] = victim_frame;
    frame_queue.push(virtual_page);
    std::cout << "Page fault: Replaced virtual page " << victim_page << " with " << virtual_page << " in frame " << victim_frame << std::endl;
    return victim_frame;
}

// Function to translate a virtual address to a physical address
int translate_address(int virtual_address) {
    int virtual_page = virtual_address / PAGE_SIZE;
    int offset = virtual_address % PAGE_SIZE;
    // Check if the page is already mapped
    if (mapped_pages.find(virtual_page) != mapped_pages.end()) {
        return mapped_pages[virtual_page] * PAGE_SIZE + offset;
    }
    // Page fault occurred - map the page to a physical frame
    int physical_frame = map_virtual_to_physical(virtual_page);
    return physical_frame * PAGE_SIZE + offset;
}

int main() {
    // Initialize free frames (assuming 4 physical frames)
    for (int i = 0; i < NUM_FRAMES; ++i) {
        free_frames.push(i);
    }
    // Test case 1: Accessing a virtual address that's not mapped
    int virtual_address = 0x1000;  // PAGE_SIZE is 4096
    int physical_address = translate_address(virtual_address);
    printf("Virtual Address 0x%X maps to Physical Address 0x%X\n", virtual_address, physical_address);
    // Test case 2: Accessing the same virtual address again
    physical_address = translate_address(virtual_address);
    printf("Virtual Address 0x%X maps to Physical Address 0x%X\n", virtual_address, physical_address);
    // Test case 3: Accessing a different virtual address (should cause a page fault)
    virtual_address = 0x2000;
    physical_address = translate_address(virtual_address);
    printf("Virtual Address 0x%X maps to Physical Address 0x%X\n", virtual_address, physical_address);
    // Test case 4: Fill up all frames and cause replacement
    translate_address(0x3000);
    translate_address(0x4000);
    // Access an old page to see replacement
    translate_address(0x1000);
    return 0;
} 