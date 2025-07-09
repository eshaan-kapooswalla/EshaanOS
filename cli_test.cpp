#include "file_system.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Simulate user input and test eshaanOS CLI commands
void testEshaanOSCLI() {
    FileSystem eshaanOSfs;
    vector<string> commands = {
        "help",
        "create test.txt",
        "write test.txt Hello, World!",
        "read test.txt",
        "ls",
        "delete test.txt",
        "read test.txt",
        "create ", // Invalid
        "delete non_existent.txt", // Invalid
        "write test.txt", // Invalid
        "invalid_command"
    };
    string content;
    for (const auto& command : commands) {
        cout << "\n--- Executing: " << command << " ---" << endl;
        if (command == "help") {
            cout << "Available commands:\nhelp\ncreate <file>\ndelete <file>\nread <file>\nwrite <file> <text>\nls\nexit\n";
        } else if (command.find("create ") == 0) {
            string fileName = command.substr(7);
            if (fileName.empty()) {
                cout << "Error: No file name provided." << endl;
            } else {
                eshaanOSfs.createFile(fileName);
            }
        } else if (command.find("delete ") == 0) {
            string fileName = command.substr(7);
            if (fileName.empty()) {
                cout << "Error: No file name provided." << endl;
            } else {
                eshaanOSfs.deleteFile(fileName);
            }
        } else if (command.find("read ") == 0) {
            string fileName = command.substr(5);
            if (fileName.empty()) {
                cout << "Error: No file name provided." << endl;
            } else {
                eshaanOSfs.readFile(fileName, content);
            }
        } else if (command.find("write ") == 0) {
            size_t firstSpace = command.find(' ');
            size_t secondSpace = command.find(' ', firstSpace + 1);
            if (secondSpace == string::npos) {
                cout << "Usage: write <file> <text>" << endl;
                continue;
            }
            string fileName = command.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string text = command.substr(secondSpace + 1);
            if (fileName.empty() || text.empty()) {
                cout << "Usage: write <file> <text>" << endl;
            } else {
                eshaanOSfs.writeFile(fileName, text);
            }
        } else if (command == "ls") {
            vector<string> directory = eshaanOSfs.listDirectory();
            if (directory.empty()) {
                cout << "Directory is empty." << endl;
            } else {
                cout << "Files in directory:" << endl;
                for (const string& file : directory) {
                    cout << file << endl;
                }
            }
        } else {
            cout << "Unknown command. Type 'help' for available commands." << endl;
        }
    }
}

int main() {
    cout << "--- eshaanOS CLI Automated Test ---" << endl;
    testEshaanOSCLI();
    return 0;
} 