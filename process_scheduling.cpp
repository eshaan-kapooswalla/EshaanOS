#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <list>
#include <functional>
#include <thread>
#include <mutex>
#include <chrono>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority; // For future use
};

struct Metrics {
    int waitingTime;
    int turnaroundTime;
};

// Extended Process struct for status display
enum class ProcessState { Running, Waiting, Stopped };

struct ProcessStatus {
    int processId;
    std::string name;
    ProcessState state;
    int priority;
    unsigned long memory;   // in bytes
    unsigned long cpuTime;  // in milliseconds
};

std::vector<ProcessStatus> processStatusList;

// Memory management structures and functions
struct MemoryFrame {
    bool isOccupied = false;
    int processId = -1;
    int virtualAddress = 0;
};

MemoryFrame* physicalMemory = nullptr;
int totalFrames = 0;

void displayPhysicalMemory() {
    std::cout << "Physical Memory State:\n";
    std::cout << "-------------------------\n";
    for (int i = 0; i < totalFrames; i++) {
        if (physicalMemory[i].isOccupied) {
            std::cout << "Frame " << i << ": Occupied by Process "
                      << physicalMemory[i].processId
                      << " (Virtual Address: "
                      << std::hex << physicalMemory[i].virtualAddress << std::dec << ")\n";
        } else {
            std::cout << "Frame " << i << ": Free\n";
        }
    }
}

void displayMemoryUsage() {
    int used = 0;
    for (int i = 0; i < totalFrames; i++) {
        if (physicalMemory[i].isOccupied) {
            used++;
        }
    }
    int total = totalFrames;
    int percentage = (total > 0) ? (used * 100) / total : 0;
    std::cout << "\nMemory Usage Statistics:\n";
    std::cout << "-------------------------\n";
    std::cout << "Total Frames: " << total << "\n";
    std::cout << "Used Frames: " << used << "\n";
    std::cout << "Memory Usage: " << percentage << "%\n";
}

// File system node structure
struct FileNode {
    std::string name;
    bool isDirectory;
    size_t size; // 0 for directories
    FileNode* parent;
    std::list<FileNode*> children;
};

// Function to display the file system state
void displayFileSystem(FileNode* root) {
    if (root == nullptr) {
        std::cout << "File system is empty." << std::endl;
        return;
    }
    std::function<void(FileNode*, int)> displayHelper =
        [&](FileNode* node, int level) {
            for (int i = 0; i < level; ++i) {
                std::cout << "    ";
            }
            std::cout << node->name;
            if (node->isDirectory) {
                std::cout << "/";
            } else {
                std::cout << " (" << node->size << " bytes)";
            }
            std::cout << std::endl;
            for (FileNode* child : node->children) {
                displayHelper(child, level + 1);
            }
        };
    std::cout << "\nCurrent File System State:" << std::endl;
    displayHelper(root, 0);
}

void updateSystemState(FileNode* fsRoot = nullptr) {
    // Process status display
    displayProcesses();
    // Memory usage display
    displayPhysicalMemory();
    displayMemoryUsage();
    // File system state display
    if (fsRoot) displayFileSystem(fsRoot);
}

std::string stateToString(ProcessState state) {
    switch (state) {
        case ProcessState::Running: return "Running";
        case ProcessState::Waiting: return "Waiting";
        case ProcessState::Stopped: return "Stopped";
        default: return "Unknown";
    }
}

void createSampleProcesses() {
    processStatusList.push_back({1, "SystemInit", ProcessState::Running, 8, 1024, 1500});
    processStatusList.push_back({2, "UserShell", ProcessState::Waiting, 4, 512, 300});
    processStatusList.push_back({3, "BackgroundTask", ProcessState::Running, 6, 768, 900});
}

void displayProcesses() {
    if (processStatusList.empty()) {
        std::cout << "No processes are currently running.\n";
        return;
    }
    std::cout << "\nCurrent Processes:\n";
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "| PID  | Name          | State    | Priority | Memory (KB) | CPU Time (ms) |\n";
    std::cout << "---------------------------------------------------------------------\n";
    for (const auto& process : processStatusList) {
        std::cout << "| " << std::setw(4) << process.processId
                  << " | " << std::setw(13) << process.name
                  << " | " << std::setw(8) << stateToString(process.state)
                  << " | " << std::setw(8) << process.priority
                  << " | " << std::setw(11) << (process.memory / 1024)
                  << " | " << std::setw(14) << process.cpuTime
                  << " |\n";
        std::cout << "---------------------------------------------------------------------\n";
    }
}

void implementFCFS(const std::vector<Process>& processes) {
    std::vector<Metrics> metrics(processes.size());
    int currentTime = 0;
    int totalWaiting = 0, totalTurnaround = 0;
    std::cout << "Execution Order (FCFS):\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        const Process& p = processes[i];
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        metrics[i].waitingTime = currentTime - p.arrivalTime;
        metrics[i].turnaroundTime = metrics[i].waitingTime + p.burstTime;
        totalWaiting += metrics[i].waitingTime;
        totalTurnaround += metrics[i].turnaroundTime;
        std::cout << "Time " << currentTime << ": Process " << p.id << " starts (Arrival: " << p.arrivalTime << ", Burst: " << p.burstTime << ")\n";
        currentTime += p.burstTime;
        std::cout << "Time " << currentTime << ": Process " << p.id << " finishes\n";
    }
    std::cout << "\nProcess\tWaiting\tTurnaround\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id << "\t" << metrics[i].waitingTime << "\t" << metrics[i].turnaroundTime << "\n";
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << (double)totalWaiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (double)totalTurnaround / processes.size() << "\n";
}

void implementSJF(const std::vector<Process>& processes) {
    struct ProcWithIndex {
        Process p;
        size_t originalIndex;
        bool completed = false;
    };
    std::vector<ProcWithIndex> procList;
    for (size_t i = 0; i < processes.size(); ++i) {
        procList.push_back({processes[i], i, false});
    }
    std::vector<Metrics> metrics(processes.size());
    int currentTime = 0;
    int completedCount = 0;
    int totalWaiting = 0, totalTurnaround = 0;
    std::cout << "Execution Order (SJF):\n";
    while (completedCount < (int)processes.size()) {
        int idx = -1;
        int minBurst = INT32_MAX;
        for (size_t i = 0; i < procList.size(); ++i) {
            if (!procList[i].completed && procList[i].p.arrivalTime <= currentTime) {
                if (procList[i].p.burstTime < minBurst) {
                    minBurst = procList[i].p.burstTime;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            // No process has arrived yet
            currentTime++;
            continue;
        }
        ProcWithIndex& chosen = procList[idx];
        metrics[chosen.originalIndex].waitingTime = currentTime - chosen.p.arrivalTime;
        metrics[chosen.originalIndex].turnaroundTime = metrics[chosen.originalIndex].waitingTime + chosen.p.burstTime;
        totalWaiting += metrics[chosen.originalIndex].waitingTime;
        totalTurnaround += metrics[chosen.originalIndex].turnaroundTime;
        std::cout << "Time " << currentTime << ": Process " << chosen.p.id << " starts (Arrival: " << chosen.p.arrivalTime << ", Burst: " << chosen.p.burstTime << ")\n";
        currentTime += chosen.p.burstTime;
        std::cout << "Time " << currentTime << ": Process " << chosen.p.id << " finishes\n";
        chosen.completed = true;
        completedCount++;
    }
    std::cout << "\nProcess\tWaiting\tTurnaround\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id << "\t" << metrics[i].waitingTime << "\t" << metrics[i].turnaroundTime << "\n";
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << (double)totalWaiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << (double)totalTurnaround / processes.size() << "\n";
}

// For real-time system state display
struct RTProcess {
    int pid;
    std::string name;
    std::string status;
};

struct RTMemory {
    int used;
    int free;
    int total;
};

struct RTFileSystem {
    std::vector<std::string> files;
};

class SystemState {
private:
    std::mutex mtx;
    std::vector<RTProcess> processes;
    RTMemory memory;
    RTFileSystem fileSystem;
public:
    void updateProcesses(const std::vector<RTProcess>& newProcesses) {
        std::lock_guard<std::mutex> lock(mtx);
        processes = newProcesses;
    }
    void updateMemory(const RTMemory& newMemory) {
        std::lock_guard<std::mutex> lock(mtx);
        memory = newMemory;
    }
    void updateFileSystem(const RTFileSystem& newFileSystem) {
        std::lock_guard<std::mutex> lock(mtx);
        fileSystem = newFileSystem;
    }
    void displaySystemState() {
        std::lock_guard<std::mutex> lock(mtx);
        // Clear the screen
        std::cout << "\033[2J\033[1;1H";
        std::cout << "+---------------------+---------------------+---------------------+\n";
        std::cout << "|     Processes      |       Memory        |     File System     |\n";
        std::cout << "+---------------------+---------------------+---------------------+\n";
        std::cout << "| PID | Name   | Status | Used | Free | Total | Files            |\n";
        std::cout << "+---------------------+---------------------+---------------------+\n";
        size_t maxRows = std::max({processes.size(), (size_t)1, fileSystem.files.size()});
        for (size_t i = 0; i < maxRows; ++i) {
            std::cout << "| ";
            if (i < processes.size()) {
                std::cout << std::setw(3) << processes[i].pid << " | "
                          << std::setw(6) << processes[i].name << " | "
                          << std::setw(6) << processes[i].status << " | ";
            } else {
                std::cout << "    |        |        | ";
            }
            if (i == 0) {
                std::cout << std::setw(4) << memory.used << " | "
                          << std::setw(4) << memory.free << " | "
                          << std::setw(5) << memory.total << " | ";
            } else {
                std::cout << "     |      |       | ";
            }
            if (i < fileSystem.files.size()) {
                std::cout << std::setw(15) << fileSystem.files[i];
            } else {
                std::cout << std::setw(15) << " ";
            }
            std::cout << " |\n";
            std::cout << "+---------------------+---------------------+---------------------+\n";
        }
    }
};

void updateSystemStateThread(SystemState& systemState) {
    while (true) {
        systemState.displaySystemState();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// TEST HARNESS FOR SYSTEM STATE DISPLAY
void clearAllProcesses(SystemState& systemState) {
    systemState.updateProcesses({});
}

void clearFileSystem(SystemState& systemState) {
    systemState.updateFileSystem(RTFileSystem{});
}

void resetMemory(SystemState& systemState, int totalFrames) {
    systemState.updateMemory(RTMemory{0, totalFrames, totalFrames});
}

void testEmptySystemState(SystemState& systemState, int totalFrames) {
    clearAllProcesses(systemState);
    clearFileSystem(systemState);
    resetMemory(systemState, totalFrames);
    std::cout << "\n[TEST] Empty System State\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void testSingleProcessRunning(SystemState& systemState, int totalFrames) {
    systemState.updateProcesses({{1, "TestProcess", "Running"}});
    systemState.updateMemory(RTMemory{1, totalFrames-1, totalFrames});
    systemState.updateFileSystem(RTFileSystem{});
    std::cout << "\n[TEST] Single Process Running\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void testMultipleProcesses(SystemState& systemState, int totalFrames) {
    systemState.updateProcesses({
        {1, "Process1", "Running"},
        {2, "Process2", "Waiting"},
        {3, "Process3", "Stopped"}
    });
    systemState.updateMemory(RTMemory{2, totalFrames-2, totalFrames});
    systemState.updateFileSystem(RTFileSystem{});
    std::cout << "\n[TEST] Multiple Processes\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void testMemoryAllocation(SystemState& systemState, int totalFrames) {
    systemState.updateProcesses({{1, "MemHog", "Running"}});
    systemState.updateMemory(RTMemory{totalFrames, 0, totalFrames});
    systemState.updateFileSystem(RTFileSystem{});
    std::cout << "\n[TEST] Memory Allocation (All Used)\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void testFileSystemOperations(SystemState& systemState, int totalFrames) {
    systemState.updateProcesses({});
    systemState.updateMemory(RTMemory{0, totalFrames, totalFrames});
    systemState.updateFileSystem(RTFileSystem{{"testfile.txt", "testdir/", "testdir/file2.txt"}});
    std::cout << "\n[TEST] File System Operations\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Simulate delete
    systemState.updateFileSystem(RTFileSystem{});
    std::cout << "\n[TEST] File System After Deletion\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void testEdgeCases(SystemState& systemState, int totalFrames, int maxProcesses) {
    std::vector<RTProcess> manyProcs;
    for (int i = 0; i < maxProcesses; ++i) {
        manyProcs.push_back({i+1, "Proc" + std::to_string(i+1), "Running"});
    }
    systemState.updateProcesses(manyProcs);
    systemState.updateMemory(RTMemory{maxProcesses, totalFrames-maxProcesses, totalFrames});
    systemState.updateFileSystem(RTFileSystem{});
    std::cout << "\n[TEST] Edge Case: Max Processes\n";
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Try to add one more process (simulate error)
    std::cout << "\n[TEST] Edge Case: Overflow Process (Should Fail or Show Error)\n";
    manyProcs.push_back({maxProcesses+1, "OverflowProc", "Running"});
    systemState.updateProcesses(manyProcs);
    systemState.displaySystemState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void runAllTests(SystemState& systemState, int totalFrames, int maxProcesses) {
    testEmptySystemState(systemState, totalFrames);
    testSingleProcessRunning(systemState, totalFrames);
    testMultipleProcesses(systemState, totalFrames);
    testMemoryAllocation(systemState, totalFrames);
    testFileSystemOperations(systemState, totalFrames);
    testEdgeCases(systemState, totalFrames, maxProcesses);
}

int main() {
    // Original scheduling demo
    std::vector<Process> processes = {
        {1, 0, 10, 1},
        {2, 1, 5, 2},
        {3, 2, 8, 3},
        {4, 3, 3, 4}
    };

    std::cout << "FCFS Scheduling:\n";
    implementFCFS(processes);

    std::cout << "\nSJF Scheduling:\n";
    implementSJF(processes);

    // Process status display demo
    std::cout << "\nProcess Status Display Example:\n";
    createSampleProcesses();
    displayProcesses();

    // Memory usage display demo
    std::cout << "\nMemory Usage Display Example:\n";
    totalFrames = 10;
    physicalMemory = new MemoryFrame[totalFrames];
    // Simulate some memory usage
    physicalMemory[0].isOccupied = true;
    physicalMemory[0].processId = 1;
    physicalMemory[0].virtualAddress = 0x1000;
    physicalMemory[1].isOccupied = true;
    physicalMemory[1].processId = 2;
    physicalMemory[1].virtualAddress = 0x2000;

    // Sample file system tree
    FileNode* root = new FileNode{"root", true, 0, nullptr, {}};
    FileNode* file1 = new FileNode{"file1.txt", false, 1024, root, {}};
    FileNode* dir1 = new FileNode{"dir1", true, 0, root, {}};
    FileNode* file2 = new FileNode{"file2.txt", false, 512, dir1, {}};
    root->children.push_back(file1);
    root->children.push_back(dir1);
    dir1->children.push_back(file2);

    // Show system state (processes + memory + file system)
    updateSystemState(root);

    // Sample data for real-time display
    SystemState systemState;
    std::vector<RTProcess> rtProcesses = {
        {1, "Init", "Running"},
        {2, "Shell", "Waiting"},
        {3, "TaskA", "Sleeping"}
    };
    RTMemory rtMemory = {2, 8, 10};
    RTFileSystem rtFS = {{"file1.txt", "dir1/", "dir1/file2.txt"}};
    systemState.updateProcesses(rtProcesses);
    systemState.updateMemory(rtMemory);
    systemState.updateFileSystem(rtFS);
    // Start real-time display thread
    std::thread updateThread(updateSystemStateThread, std::ref(systemState));
    // Simulate main program running for a few seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // End program (thread will be terminated)
    updateThread.detach();

    // Run all system state display tests
    int totalFrames = 10;
    int maxProcesses = 8;
    runAllTests(systemState, totalFrames, maxProcesses);

    // Cleanup
    delete file2;
    delete dir1;
    delete file1;
    delete root;
    delete[] physicalMemory;
    return 0;
} 