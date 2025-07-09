#include <iostream>
#include <vector>
#include <iomanip>
#include "page_table.h"
#include "physical_memory.h"
#include "fifo_policy.h"
#include "memory_manager.h"

using namespace std;

void test_page_table_mapping(MemoryManager& mm, int virtual_address, int expected_frame) {
    int virtual_page = virtual_address / 4096;
    int actual_frame = mm.handlePageFault(virtual_page);
    if (actual_frame == expected_frame) {
        cout << "Paging test passed: Virtual 0x" << hex << virtual_address 
             << " maps to frame " << dec << actual_frame << endl;
    } else {
        cout << "Paging test failed: Expected frame " << expected_frame 
             << ", got " << actual_frame << endl;
    }
}

void test_page_fault_handling(MemoryManager& mm, int virtual_address) {
    int virtual_page = virtual_address / 4096;
    int frame = mm.handlePageFault(virtual_page);
    if (frame != -1) {
        cout << "Page fault test passed: Page fault handled for virtual address 0x" << hex << virtual_address << endl;
    } else {
        cout << "Page fault test failed: No frame allocated for virtual address 0x" << hex << virtual_address << endl;
    }
}

void test_frame_replacement_policy() {
    cout << "\nTest case 4: Frame Replacement (FIFO)" << endl;
    PageTable pt(3);
    PhysicalMemory pm(3);
    FIFOPolicy policy;
    MemoryManager mm(&pt, &pm, &policy);
    vector<int> virtual_addresses = {0x1000, 0x2000, 0x3000, 0x4000};
    vector<int> expected_frames = {1, 2, 0, 1}; // After 4th access, frame 0 should be replaced
    for (size_t i = 0; i < virtual_addresses.size(); ++i) {
        int virtual_page = virtual_addresses[i] / 4096;
        int frame = mm.handlePageFault(virtual_page);
        cout << "Accessed virtual address 0x" << hex << virtual_addresses[i] << ", mapped to frame " << dec << frame << endl;
    }
    // Print final frame contents
    cout << "Final physical frames: ";
    int* frames = pm.getFrames();
    for (int i = 0; i < pm.getNumFrames(); ++i) {
        cout << frames[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Test case 1: Simple Paging" << endl;
    PageTable pt1(3);
    PhysicalMemory pm1(3);
    FIFOPolicy policy1;
    MemoryManager mm1(&pt1, &pm1, &policy1);
    test_page_table_mapping(mm1, 0x1000, 0); // Page 1, should map to frame 0

    cout << "\nTest case 2: Multiple Pages" << endl;
    PageTable pt2(3);
    PhysicalMemory pm2(3);
    FIFOPolicy policy2;
    MemoryManager mm2(&pt2, &pm2, &policy2);
    vector<int> virtual_addresses = {0x1000, 0x2000, 0x3000};
    vector<int> expected_frames = {0, 1, 2};
    for (size_t i = 0; i < virtual_addresses.size(); ++i) {
        test_page_table_mapping(mm2, virtual_addresses[i], expected_frames[i]);
    }

    cout << "\nTest case 3: Page Fault Handling" << endl;
    PageTable pt3(3);
    PhysicalMemory pm3(3);
    FIFOPolicy policy3;
    MemoryManager mm3(&pt3, &pm3, &policy3);
    test_page_fault_handling(mm3, 0x4000); // Page 4, not mapped

    test_frame_replacement_policy();
    return 0;
} 