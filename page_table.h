#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <vector>

class PageTable {
private:
    std::vector<int> pageToFrameMap;
    int numPages;
public:
    PageTable(int pages) : numPages(pages) {
        pageToFrameMap.resize(numPages, -1);
    }
    int getPhysicalFrame(int virtualPage) {
        if (virtualPage >= 0 && virtualPage < numPages) {
            return pageToFrameMap[virtualPage];
        }
        return -1;
    }
    void mapPage(int virtualPage, int physicalFrame) {
        if (virtualPage >= 0 && virtualPage < numPages) {
            pageToFrameMap[virtualPage] = physicalFrame;
        }
    }
    void unmapPage(int virtualPage) {
        if (virtualPage >= 0 && virtualPage < numPages) {
            pageToFrameMap[virtualPage] = -1;
        }
    }
};

#endif // PAGE_TABLE_H 