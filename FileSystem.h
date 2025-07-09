#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include "Directory.h"

class FileSystem {
private:
    Directory root;
public:
    FileSystem() : root("/") {}
    bool createFile(const std::string& path, const std::string& content = "");
    bool createDirectory(const std::string& path);
    bool deleteFile(const std::string& path);
    bool deleteDirectory(const std::string& path);
    File* readFile(const std::string& path);
    bool writeFile(const std::string& path, const std::string& content);
};

#endif // FILESYSTEM_H 