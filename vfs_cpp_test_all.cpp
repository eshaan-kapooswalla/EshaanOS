#include <iostream>
#include <cstring>
#include "FileSystem.h"

void printFileContent(FileSystem& vfs, const std::string& path) {
    File* file = vfs.readFile(path);
    if (file) {
        std::cout << "Content of '" << path << "':\n" << file->getContent() << "\n";
    } else {
        std::cout << "File '" << path << "' does not exist.\n";
    }
}

void listDirectory(FileSystem& vfs, const std::string& path) {
    std::cout << "Listing contents of '" << path << "':\n";
    std::vector<std::string> pathComponents;
    std::stringstream ss(path);
    std::string component;
    while (std::getline(ss, component, '/')) {
        if (!component.empty()) pathComponents.push_back(component);
    }
    Directory* current = &vfs.root;
    for (const auto& comp : pathComponents) {
        if (current->subdirectories.find(comp) != current->subdirectories.end()) {
            current = &current->subdirectories[comp];
        } else {
            std::cout << "Directory not found: " << comp << "\n";
            return;
        }
    }
    std::cout << "Subdirectories:\n";
    for (const auto& subdir : current->subdirectories) {
        std::cout << "- " << subdir.first << "\n";
    }
    std::cout << "Files:\n";
    for (const auto& file : current->files) {
        std::cout << "- " << file.first << "\n";
    }
}

int main() {
    FileSystem vfs;
    // Test file creation
    std::cout << "Creating file 'test_file1.txt'...\n";
    bool result = vfs.createFile("test_file1.txt");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    std::cout << "Creating file 'test_file2.txt'...\n";
    result = vfs.createFile("test_file2.txt");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    std::cout << "Creating directory 'test_dir'...\n";
    result = vfs.createDirectory("test_dir");
    std::cout << (result ? "Success" : "Failed") << std::endl;

    // Test file deletion
    std::cout << "Deleting file 'test_file1.txt'...\n";
    result = vfs.deleteFile("test_file1.txt");
    std::cout << (result ? "Success" : "Failed") << std::endl;

    // Test file reading (should be empty)
    std::cout << "Reading 'test_file2.txt'...\n";
    printFileContent(vfs, "test_file2.txt");

    // Test file writing
    std::cout << "Writing to 'test_file2.txt'...\n";
    result = vfs.writeFile("test_file2.txt", "Hello, Virtual File System!");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    printFileContent(vfs, "test_file2.txt");

    // Test directory management
    std::cout << "Creating file 'test_dir/test_file3.txt'...\n";
    result = vfs.createFile("test_dir/test_file3.txt");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    listDirectory(vfs, "test_dir");
    std::cout << "Deleting directory 'test_dir' (should fail if not empty)...\n";
    result = vfs.deleteDirectory("test_dir");
    std::cout << (result ? "Success" : "Failed (as expected)" ) << std::endl;
    std::cout << "Deleting file 'test_dir/test_file3.txt'...\n";
    result = vfs.deleteFile("test_dir/test_file3.txt");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    std::cout << "Deleting directory 'test_dir'...\n";
    result = vfs.deleteDirectory("test_dir");
    std::cout << (result ? "Success" : "Failed") << std::endl;

    // Edge case: create duplicate file
    std::cout << "Creating file 'test_file2.txt' again...\n";
    result = vfs.createFile("test_file2.txt");
    std::cout << (result ? "Success (unexpected)" : "File already exists (expected)") << std::endl;

    // Edge case: delete non-existent file
    std::cout << "Deleting non-existent file 'non_existent_file.txt'...\n";
    result = vfs.deleteFile("non_existent_file.txt");
    std::cout << (result ? "Success (unexpected)" : "File not found (expected)") << std::endl;

    // Edge case: read from an empty file
    std::cout << "Creating empty file 'empty_file.txt'...\n";
    result = vfs.createFile("empty_file.txt");
    std::cout << (result ? "Success" : "Failed") << std::endl;
    std::cout << "Reading 'empty_file.txt'...\n";
    printFileContent(vfs, "empty_file.txt");

    return 0;
} 