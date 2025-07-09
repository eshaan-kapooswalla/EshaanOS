#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <map>
#include <vector>

class FileSystem {
private:
    std::map<std::string, std::string> files;  // Stores file names and their contents
    std::string currentDirectory;             // Simulates the current working directory
public:
    FileSystem();
    ~FileSystem();
    bool createFile(const std::string& fileName, const std::string& content = "");
    bool deleteFile(const std::string& fileName);
    bool readFile(const std::string& fileName, std::string& content);
    bool writeFile(const std::string& fileName, const std::string& content);
    std::vector<std::string> listDirectory();
    void formatFileName(std::string& fileName);
    bool fileExists(const std::string& fileName);
};

#endif // FILE_SYSTEM_H 