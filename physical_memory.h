#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

class PhysicalMemory {
private:
    int* frames;
    int numFrames;
public:
    PhysicalMemory(int framesCount) : numFrames(framesCount) {
        frames = new int[numFrames];
        for (int i = 0; i < numFrames; i++) {
            frames[i] = -1;
        }
    }
    ~PhysicalMemory() {
        delete[] frames;
    }
    int* getFrames() { return frames; }
    int getNumFrames() const { return numFrames; }
    bool isFrameEmpty(int frame) { return frames[frame] == -1; }
    void loadPage(int frame, int page) { frames[frame] = page; }
    void unloadPage(int frame) { frames[frame] = -1; }
};

#endif // PHYSICAL_MEMORY_H 