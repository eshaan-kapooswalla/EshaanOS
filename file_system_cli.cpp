#include "file_system.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void displayHelp() {
    cout << "Available commands:" << endl;
    cout << "help                - Display this help menu" << endl;
    cout << "create <file>       - Create a new file" << endl;
    cout << "delete <file>       - Delete an existing file" << endl;
    cout << "read <file>         - Display the contents of a file" << endl;
    cout << "write <file> <text> - Write or update text in a file" << endl;
    cout << "ls                  - List all files in the current directory" << endl;
    cout << "exit                - Quit the simulator" << endl;
}

int main() {
    FileSystem fs;
    string input;
    cout << "Welcome to the Operating System Simulator!" << endl;
    displayHelp();
    while (true) {
        cout << "os-simulator> ";
        getline(cin, input);
        if (input == "exit") {
            break;
        } else if (input == "help") {
            displayHelp();
        } else if (input.find("create ") == 0) {
            string fileName = input.substr(7);
            fs.createFile(fileName);
        } else if (input.find("delete ") == 0) {
            string fileName = input.substr(7);
            fs.deleteFile(fileName);
        } else if (input.find("read ") == 0) {
            string fileName = input.substr(5);
            string content;
            fs.readFile(fileName, content);
        } else if (input.find("write ") == 0) {
            size_t firstSpace = input.find(' ');
            size_t secondSpace = input.find(' ', firstSpace + 1);
            if (secondSpace == string::npos) {
                cout << "Usage: write <file> <text>" << endl;
                continue;
            }
            string fileName = input.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string content = input.substr(secondSpace + 1);
            fs.writeFile(fileName, content);
        } else if (input == "ls") {
            vector<string> directory = fs.listDirectory();
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
    return 0;
} 