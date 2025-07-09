#include "Directory.h"
#include <ctime>

Directory::Directory(const std::string& name) : name(name) {}

bool Directory::createFile(const std::string& fileName, const std::string& content) {
    if (files.find(fileName) != files.end()) {
        return false; // File already exists
    }
    File newFile(fileName, content);
    files[fileName] = newFile;
    return true;
}

bool Directory::createDirectory(const std::string& dirName) {
    if (subdirectories.find(dirName) != subdirectories.end()) {
        return false; // Directory already exists
    }
    Directory newDir(dirName);
    subdirectories[dirName] = newDir;
    return true;
}

bool Directory::deleteFile(const std::string& fileName) {
    if (files.find(fileName) == files.end()) {
        return false; // File does not exist
    }
    files.erase(fileName);
    return true;
}

bool Directory::deleteDirectory(const std::string& dirName) {
    if (subdirectories.find(dirName) == subdirectories.end()) {
        return false; // Directory does not exist
    }
    subdirectories.erase(dirName);
    return true;
}

File* Directory::readFile(const std::string& fileName) {
    if (files.find(fileName) == files.end()) {
        return nullptr; // File does not exist
    }
    return &files[fileName];
}

bool Directory::writeFile(const std::string& fileName, const std::string& content) {
    if (files.find(fileName) == files.end()) {
        return false; // File does not exist
    }
    files[fileName].setContent(content);
    return true;
} 