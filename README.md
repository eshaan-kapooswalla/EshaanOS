# EshaanOS

EshaanOS is a modular, educational operating system simulation written in C++. It provides a platform for experimenting with core OS concepts such as process scheduling, memory management, and virtual file systems. The project is designed for learning, research, and demonstration purposes.

---

## Features

- **Process Scheduling**
  - Implements multiple scheduling algorithms: FCFS (First-Come, First-Served) and SJF (Shortest Job First), with a flexible scheduler factory for extensibility.
  - CLI and test modules for creating, listing, and managing processes.
  - Real-time and batch simulation of process execution, including process states and metrics (waiting time, turnaround time, etc.).

- **Memory Management & Paging**
  - Simulates virtual memory, page tables, and physical memory.
  - Supports page replacement policies: FIFO (First-In, First-Out) and LRU (Least Recently Used).
  - Includes TLB (Translation Lookaside Buffer) simulation and memory usage statistics.
  - Test modules for page fault handling and frame replacement.

- **Virtual File System (VFS)**
  - Hierarchical file and directory structure with support for file creation, deletion, reading, and writing.
  - Directory and file abstractions with metadata (size, timestamps).
  - CLI and test modules for file system operations, including error handling and directory management.

- **Command-Line Interface (CLI)**
  - Interactive CLI for managing files, directories, processes, and memory.
  - Built-in help menus and command descriptions.

- **System Monitoring**
  - Tools for monitoring system state, processes, and memory usage.
  - Real-time display of processes, memory, and file system state.

---

## Architecture Overview

- **Process Scheduling**
  - `EshaanOS_Scheduler.h`, `fcfs_EshaanOS_Scheduler.cpp`, `sjf_EshaanOS_Scheduler.cpp`, and related headers define the scheduler interface and implementations.
  - `SchedulerFactory` creates scheduler instances based on the selected algorithm.
  - Process structures include fields for ID, name, arrival/burst time, priority, and state.

- **Memory Management**
  - `memory_manager.h`, `page_table.h`, `physical_memory.h`, and policy headers implement virtual memory, page tables, and page replacement.
  - `MemoryManager` handles page faults, frame allocation, and replacement using pluggable policies.
  - Test modules (`memory_management_test.cpp`, `paging_simulation.cpp`, etc.) demonstrate paging and replacement.

- **Virtual File System**
  - `FileSystem.h`, `Directory.h`, `File.h`, and their implementations provide a hierarchical VFS.
  - Supports nested directories, file metadata, and content management.
  - CLI and test modules (`file_system_cli.cpp`, `vfs_cpp_test_all.cpp`, etc.) provide user interaction and validation.

- **CLI & Monitoring**
  - `cli_manager.cpp` and `system_monitoring.cpp` implement interactive command-line interfaces for OS simulation and monitoring.

---

## Directory Structure

```
.
├── cli_manager.cpp                # CLI management logic
├── Directory.*                    # Directory abstraction
├── EshaanOS_Scheduler*            # Scheduler interfaces and types
├── fcfs_EshaanOS_Scheduler*       # FCFS scheduling implementation
├── sjf_EshaanOS_Scheduler*        # SJF scheduling implementation
├── file_system*                   # File system core logic
├── File.*                         # File abstraction
├── FileSystem.*                   # File system interface
├── memory_management_*            # Memory management structures and tests
├── page_*                         # Paging and page replacement policies
├── process_*                      # Process management and scheduling
├── vfs_cpp_*                      # VFS operations (creation, deletion, reading, writing)
├── system_monitoring.cpp          # System monitoring utilities
└── ...                            # Additional modules and tests
```

---

## Getting Started

### Prerequisites
- C++17 or later
- CMake (recommended) or a compatible build system
- A POSIX-compliant environment (Linux/macOS recommended)

### Build Instructions

1. **Clone the repository:**
   ```sh
   git clone <repo-url>
   cd EshaanOS
   ```
2. **Build the project:**
   ```sh
   g++ -std=c++17 -o eshaan_os *.cpp
   ```
   Or use CMake for more advanced builds.

3. **Run the simulation:**
   ```sh
   ./eshaan_os
   ```

### Running Tests

Test files are provided for various modules (e.g., `ProcessEshaanOS_Scheduler_test.cpp`, `memory_management_test.cpp`). Compile and run them individually:

```sh
g++ -std=c++17 -o test_process_scheduler ProcessEshaanOS_Scheduler_test.cpp
./test_process_scheduler
```

---

## Usage

- **Process Scheduling:**
  - Experiment with different scheduling algorithms by modifying the scheduler factory and running the relevant simulation files.
  - Use the CLI to create, list, and manage processes.

- **Memory Management:**
  - Simulate paging and page replacement by running `paging_simulation.cpp` or `physical_memory_sim.cpp`.
  - Test page fault handling and replacement policies with provided test modules.

- **File System:**
  - Use the CLI or VFS modules to create, read, write, and delete files and directories.
  - Explore directory management and error handling with test modules.

---

## Contributing

Contributions are welcome! Please open issues or submit pull requests for bug fixes, new features, or improvements.

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

## Acknowledgements

- Inspired by classic OS textbooks and university coursework.
- Thanks to all contributors and reviewers.

---

**Note:** This project is for educational purposes and is not intended for production use. 