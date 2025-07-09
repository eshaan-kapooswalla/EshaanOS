#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CLI_Manager {
private:
    vector<string> commands;
    vector<string> descriptions;
    string prompt = "> ";
public:
    CLI_Manager() {
        // Initialize commands and their descriptions
        commands = {
            "help",
            "exit",
            "clear",
            "process create",
            "process list",
            "process kill",
            "memory show",
            "file create",
            "file delete",
            "file read",
            "file write"
        };
        descriptions = {
            "Display this help menu",
            "Exit the simulator",
            "Clear the screen",
            "Create a new process",
            "List all running processes",
            "Kill a process",
            "Show memory usage",
            "Create a new file",
            "Delete a file",
            "Read from a file",
            "Write to a file"
        };
    }
    void display_help() {
        cout << "------------------------- Help Menu -------------------------" << endl;
        for (int i = 0; i < commands.size(); i++) {
            cout << commands[i] << " - " << descriptions[i] << endl;
        }
        cout << "----------------------------------------------------------------" << endl;
    }
    void process_input(string input) {
        // Simple command processing
        // Split the input into parts
        size_t pos = input.find(' ');
        string command = input.substr(0, pos);
        string argument = (pos != string::npos) ? input.substr(pos + 1) : "";
        if (command == "help") {
            display_help();
        } else if (command == "exit") {
            cout << "Exiting simulator..." << endl;
            exit(0);
        } else if (command == "clear") {
            cout << string(50, '\n');
        } else {
            cout << "Unknown or unimplemented command: '" << command << "'" << endl;
        }
    }
    void run() {
        cout << "------------------------- OS Simulator CLI -------------------------" << endl;
        display_help();
        while (true) {
            cout << prompt;
            string input;
            getline(cin, input);
            if (cin.fail()) {
                break;
            }
            process_input(input);
        }
    }
};

int main() {
    CLI_Manager cli;
    cli.run();
    return 0;
} 