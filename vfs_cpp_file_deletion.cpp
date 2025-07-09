#include <iostream>
#include "FileSystem.h"

int main() {
    FileSystem vfs;
    // Create files
    vfs.createFile("file1.txt", "Hello, World!");
    vfs.createFile("file2.txt", "Another file");
    vfs.createFile("dir1/file3.txt", "File in dir1");
    vfs.createDirectory("dir1");
    vfs.createFile("dir1/file4.txt", "Another file in dir1");

    // Try deleting an existing file
    std::cout << "Deleting file1.txt...\n";
    if (vfs.deleteFile("file1.txt")) {
        std::cout << "file1.txt deleted successfully.\n";
    } else {
        std::cout << "Failed to delete file1.txt\n";
    }

    // Try deleting a non-existent file
    std::cout << "Deleting non_existent.txt...\n";
    if (vfs.deleteFile("non_existent.txt")) {
        std::cout << "non_existent.txt deleted successfully.\n";
    } else {
        std::cout << "Failed to delete non_existent.txt (as expected)\n";
    }

    // Try deleting a file in a directory
    std::cout << "Deleting dir1/file4.txt...\n";
    if (vfs.deleteFile("dir1/file4.txt")) {
        std::cout << "dir1/file4.txt deleted successfully.\n";
    } else {
        std::cout << "Failed to delete dir1/file4.txt\n";
    }

    // Try deleting all files
    std::cout << "Deleting file2.txt...\n";
    if (vfs.deleteFile("file2.txt")) {
        std::cout << "file2.txt deleted successfully.\n";
    } else {
        std::cout << "Failed to delete file2.txt\n";
    }
    std::cout << "Deleting dir1/file3.txt...\n";
    if (vfs.deleteFile("dir1/file3.txt")) {
        std::cout << "dir1/file3.txt deleted successfully.\n";
    } else {
        std::cout << "Failed to delete dir1/file3.txt\n";
    }

    // Try deleting again to check error handling
    std::cout << "Deleting file2.txt again...\n";
    if (vfs.deleteFile("file2.txt")) {
        std::cout << "file2.txt deleted successfully (unexpected).\n";
    } else {
        std::cout << "Failed to delete file2.txt (as expected)\n";
    }

    return 0;
} 