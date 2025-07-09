#include <iostream>
#include "FileSystem.h"

void printFileContent(FileSystem& vfs, const std::string& path) {
    File* file = vfs.readFile(path);
    if (file) {
        std::cout << "Content of '" << path << "':\n" << file->getContent() << "\n";
    } else {
        std::cout << "File '" << path << "' does not exist.\n";
    }
}

int main() {
    FileSystem vfs;
    // Test 1: Write to a new file (overwrite mode)
    std::cout << "Writing to new file test1.txt..." << std::endl;
    bool result = vfs.writeFile("test1.txt", "Hello, World!");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    printFileContent(vfs, "test1.txt");

    // Test 2: Append to existing file
    std::cout << "\nAppending to test1.txt..." << std::endl;
    File* file = vfs.readFile("test1.txt");
    if (file) {
        std::string newContent = file->getContent() + "\nAppended line";
        result = vfs.writeFile("test1.txt", newContent);
        std::cout << (result ? "Success" : "Failed") << std::endl;
        printFileContent(vfs, "test1.txt");
    } else {
        std::cout << "File 'test1.txt' does not exist for appending." << std::endl;
    }

    // Test 3: Write to non-existent file in append mode (should fail gracefully)
    std::cout << "\nAttempting to append to non-existent file test2.txt..." << std::endl;
    file = vfs.readFile("test2.txt");
    if (file) {
        std::string newContent = file->getContent() + "Test content";
        result = vfs.writeFile("test2.txt", newContent);
        std::cout << (result ? "Success" : "Failed") << std::endl;
    } else {
        std::cout << "File 'test2.txt' does not exist. Failed" << std::endl;
    }

    return 0;
} 