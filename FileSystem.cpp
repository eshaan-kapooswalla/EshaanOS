#include "FileSystem.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> splitPath(const string& path) {
    vector<string> components;
    stringstream ss(path);
    string component;
    while (getline(ss, component, '/')) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }
    return components;
}

Directory* navigateToDirectory(Directory& currentDir, const vector<string>& pathComponents) {
    Directory* current = &currentDir;
    for (size_t i = 0; i < pathComponents.size(); ++i) {
        string component = pathComponents[i];
        if (current->subdirectories.find(component) != current->subdirectories.end()) {
            current = &current->subdirectories[component];
        } else {
            return nullptr; // Directory does not exist
        }
    }
    return current;
}

bool FileSystem::createFile(const string& path, const string& content) {
    vector<string> pathComponents = splitPath(path);
    if (pathComponents.empty()) {
        return false; // Invalid path
    }
    string fileName = pathComponents.back();
    pathComponents.pop_back();
    Directory* currentDir = navigateToDirectory(root, pathComponents);
    if (!currentDir) {
        return false; // Directory does not exist
    }
    return currentDir->createFile(fileName, content);
}

bool FileSystem::createDirectory(const string& path) {
    vector<string> pathComponents = splitPath(path);
    if (pathComponents.empty()) {
        return false; // Invalid path
    }
    Directory* currentDir = &root;
    for (size_t i = 0; i < pathComponents.size(); ++i) {
        string component = pathComponents[i];
        if (currentDir->subdirectories.find(component) != currentDir->subdirectories.end()) {
            currentDir = &currentDir->subdirectories[component];
        } else {
            Directory newDir(component);
            currentDir->subdirectories[component] = newDir;
            currentDir = &currentDir->subdirectories[component];
        }
    }
    return true;
}

bool FileSystem::deleteFile(const string& path) {
    vector<string> pathComponents = splitPath(path);
    if (pathComponents.empty()) {
        return false; // Invalid path
    }
    string fileName = pathComponents.back();
    pathComponents.pop_back();
    Directory* currentDir = navigateToDirectory(root, pathComponents);
    if (!currentDir) {
        return false; // Directory does not exist
    }
    return currentDir->deleteFile(fileName);
}

bool FileSystem::deleteDirectory(const string& path) {
    vector<string> pathComponents = splitPath(path);
    if (pathComponents.empty()) {
        return false; // Invalid path
    }
    Directory* currentDir = &root;
    for (size_t i = 0; i < pathComponents.size(); ++i) {
        string component = pathComponents[i];
        if (currentDir->subdirectories.find(component) != currentDir->subdirectories.end()) {
            if (i == pathComponents.size() - 1) {
                currentDir->subdirectories.erase(component);
                return true;
            } else {
                currentDir = &currentDir->subdirectories[component];
            }
        } else {
            return false; // Directory does not exist
        }
    }
    return false;
}

File* FileSystem::readFile(const string& path) {
    vector<string> pathComponents = splitPath(path);
    if (pathComponents.empty()) {
        return nullptr; // Invalid path
    }
    string fileName = pathComponents.back();
    pathComponents.pop_back();
    Directory* currentDir = navigateToDirectory(root, pathComponents);
    if (!currentDir) {
        return nullptr; // Directory does not exist
    }
    return currentDir->readFile(fileName);
}

bool FileSystem::writeFile(const string& path, const string& content) {
    vector<string> pathComponents = splitPath(path);
    if (pathComponents.empty()) {
        return false; // Invalid path
    }
    string fileName = pathComponents.back();
    pathComponents.pop_back();
    Directory* currentDir = navigateToDirectory(root, pathComponents);
    if (!currentDir) {
        return false; // Directory does not exist
    }
    return currentDir->writeFile(fileName, content);
} 