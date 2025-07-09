#include <iostream>
#include "FileSystem.h"

void listDirectory(FileSystem& vfs, const std::string& path) {
    std::cout << "Listing contents of '" << path << "':\n";
    // Use the Directory class directly for listing
    // We'll use the FileSystem's root and navigate as in FileSystem.cpp
    // This is a simplified version for demonstration
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
    // Create directories
    vfs.createDirectory("documents/personal");
    vfs.createDirectory("pictures");
    // List directory contents
    listDirectory(vfs, "documents");
    listDirectory(vfs, "documents/personal");
    listDirectory(vfs, "pictures");
    // Create files in directories
    vfs.createFile("documents/resume.txt", "Resume content");
    vfs.createFile("documents/personal/note.txt", "Personal note");
    // List contents again
    listDirectory(vfs, "documents/personal");
    // Delete a directory (should fail if not empty)
    std::cout << "\nAttempting to delete non-empty directory 'documents/personal'...\n";
    if (vfs.deleteDirectory("documents/personal")) {
        std::cout << "Directory deleted successfully.\n";
    } else {
        std::cout << "Failed to delete directory (as expected if not empty).\n";
    }
    // Delete file and then delete directory
    vfs.deleteFile("documents/personal/note.txt");
    if (vfs.deleteDirectory("documents/personal")) {
        std::cout << "Directory deleted successfully after removing file.\n";
    } else {
        std::cout << "Failed to delete directory.\n";
    }
    return 0;
} 