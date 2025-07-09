#include <iostream>
#include <iomanip>
#include <ctime>
#include "FileSystem.h"

void printFileInfo(File* file) {
    if (!file) {
        std::cout << "Error: File not found in the virtual file system.\n";
        return;
    }
    std::cout << "File: " << file->getName() << std::endl;
    std::cout << "Size: " << file->getSize() << " bytes" << std::endl;
    std::time_t ctime = file->getCreationTime();
    std::cout << "Created: " << std::put_time(std::localtime(&ctime), "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "Content:\n" << file->getContent() << std::endl;
}

int main() {
    FileSystem vfs;
    // Create files
    vfs.createFile("file1.txt", "Hello, World!");
    vfs.createFile("file2.txt", "Another file");
    vfs.createDirectory("dir1");
    vfs.createFile("dir1/file3.txt", "File in dir1");

    // Read existing files
    std::cout << "Reading file1.txt...\n";
    printFileInfo(vfs.readFile("file1.txt"));

    std::cout << "\nReading dir1/file3.txt...\n";
    printFileInfo(vfs.readFile("dir1/file3.txt"));

    // Try reading a non-existent file
    std::cout << "\nReading non_existent.txt...\n";
    printFileInfo(vfs.readFile("non_existent.txt"));

    return 0;
} 