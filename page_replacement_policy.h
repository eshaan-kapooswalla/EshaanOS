#ifndef PAGE_REPLACEMENT_POLICY_H
#define PAGE_REPLACEMENT_POLICY_H

class PageReplacementPolicy {
public:
    virtual ~PageReplacementPolicy() {}
    virtual int selectVictimFrame(int* pageFrames, int numFrames) = 0;
    virtual void pageLoaded(int page) = 0;
    virtual void pageAccessed(int page) {} // Optional for LRU
};

#endif // PAGE_REPLACEMENT_POLICY_H 