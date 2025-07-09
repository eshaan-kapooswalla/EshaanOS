#include "file_system.h"
#include <iostream>
#include <algorithm>

using namespace std;

FileSystem::FileSystem() : currentDirectory("root/") {}
FileSystem::~FileSystem() {}

void FileSystem::formatFileName(string& fileName) {
    if (!fileName.empty() && fileName[0] == '/') fileName.erase(0, 1);
    if (!fileName.empty() && fileName.back() == '/') fileName.pop_back();
}

bool FileSystem::fileExists(const string& fileName) {
    return files.find(fileName) != files.end();
}

bool FileSystem::createFile(const string& fileName, const string& content) {
    string formattedName = fileName;
    formatFileName(formattedName);
    if (fileExists(formattedName)) {
        cout << "Error: File already exists." << endl;
        return false;
    }
    files[formattedName] = content;
    cout << "File created successfully: " << formattedName << endl;
    return true;
}

bool FileSystem::deleteFile(const string& fileName) {
    string formattedName = fileName;
    formatFileName(formattedName);
    if (!fileExists(formattedName)) {
        cout << "Error: File not found." << endl;
        return false;
    }
    files.erase(formattedName);
    cout << "File deleted successfully: " << formattedName << endl;
    return true;
}

bool FileSystem::readFile(const string& fileName, string& content) {
    string formattedName = fileName;
    formatFileName(formattedName);
    if (!fileExists(formattedName)) {
        cout << "Error: File not found." << endl;
        return false;
    }
    content = files[formattedName];
    cout << "File contents: " << endl << content << endl;
    return true;
}

bool FileSystem::writeFile(const string& fileName, const string& content) {
    string formattedName = fileName;
    formatFileName(formattedName);
    files[formattedName] = content;
    cout << "File updated successfully: " << formattedName << endl;
    return true;
}

vector<string> FileSystem::listDirectory() {
    vector<string> directoryContents;
    for (const auto& file : files) {
        directoryContents.push_back(file.first);
    }
    return directoryContents;
} 