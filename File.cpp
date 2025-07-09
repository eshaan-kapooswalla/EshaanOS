#include "File.h"
#include <ctime>

File::File(const std::string& name, const std::string& content)
    : name(name), content(content), size(content.size()) {
    std::time(&creationTime);
    modificationTime = creationTime;
}

std::string File::getName() const { return name; }
std::string File::getContent() const { return content; }
size_t File::getSize() const { return size; }
std::time_t File::getCreationTime() const { return creationTime; }
std::time_t File::getModificationTime() const { return modificationTime; }

void File::setContent(const std::string& content) {
    this->content = content;
    size = content.size();
    std::time(&modificationTime);
} 