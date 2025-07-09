#ifndef FILE_H
#define FILE_H

#include <string>
#include <ctime>

class File {
private:
    std::string name;
    std::string content;
    size_t size;
    std::time_t creationTime;
    std::time_t modificationTime;
public:
    File(const std::string& name, const std::string& content = "");
    std::string getName() const;
    std::string getContent() const;
    size_t getSize() const;
    std::time_t getCreationTime() const;
    std::time_t getModificationTime() const;
    void setContent(const std::string& content);
};

#endif // FILE_H 