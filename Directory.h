#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <map>
#include "File.h"

class Directory {
private:
    std::string name;
    std::map<std::string, Directory> subdirectories;
    std::map<std::string, File> files;
public:
    Directory(const std::string& name);
    bool createFile(const std::string& fileName, const std::string& content = "");
    bool createDirectory(const std::string& dirName);
    bool deleteFile(const std::string& fileName);
    bool deleteDirectory(const std::string& dirName);
    File* readFile(const std::string& fileName);
    bool writeFile(const std::string& fileName, const std::string& content);
    friend class FileSystem;
};

#endif // DIRECTORY_H 