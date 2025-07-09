#include <iostream>
#include <vector>

// Enum for frame states
enum class FrameState {
    FREE,
    USED
};

// Structure to represent a physical frame
struct Frame {
    int id;                     // Unique identifier for the frame
    FrameState state;           // Current state of the frame (FREE/USED)
    int reference_count;        // Number of references to this frame
    bool dirty;                 // Indicates if the frame has been modified
};

// Class to manage physical memory
class PhysicalMemory {
private:
    std::vector<Frame> frames;         // Array of frames
    int num_frames;                    // Total number of frames
    
public:
    // Constructor to initialize physical memory with a specified number of frames
    PhysicalMemory(int frames_count) {
        num_frames = frames_count;
        initialize_frames();
    }

    // Initialize all frames with default values
    void initialize_frames() {
        for (int i = 0; i < num_frames; ++i) {
            Frame frame;
            frame.id = i;
            frame.state = FrameState::FREE;
            frame.reference_count = 0;
            frame.dirty = false;
            frames.push_back(frame);
        }
    }

    // Get the total number of frames in physical memory
    int frame_count() const {
        return num_frames;
    }

    // Get the number of free frames available
    int free_frame_count() const {
        int count = 0;
        for (const auto& frame : frames) {
            if (frame.state == FrameState::FREE) {
                count++;
            }
        }
        return count;
    }

    // Find and return the index of the first free frame
    int find_free_frame() {
        for (size_t i = 0; i < frames.size(); ++i) {
            if (frames[i].state == FrameState::FREE) {
                return static_cast<int>(i);
            }
        }
        return -1; // No free frames available
    }

    // Handle a page fault by replacing frames if necessary
    void handle_page_fault(int page_number) {
        // Implementation will come in the next task
    }

    // Helper method to check if a frame ID is valid
    bool is_valid_frame(int frame_id) const {
        return (frame_id >= 0 && frame_id < num_frames);
    }

    // Get the reference count of a specific frame
    int get_frame_reference_count(int frame_id) const {
        if (!is_valid_frame(frame_id)) {
            return -1;
        }
        return frames[frame_id].reference_count;
    }

    // Example method to display all frame information
    void display_frames_info() const {
        for (const auto& frame : frames) {
            std::cout << "Frame ID: " << frame.id << std::endl;
            std::cout << "State: " << (frame.state == FrameState::FREE ? "FREE" : "USED") << std::endl;
            std::cout << "Reference Count: " << frame.reference_count << std::endl;
            std::cout << "Dirty: " << frame.dirty << std::endl;
            std::cout << "-------------------------" << std::endl;
        }
    }
};

int main() {
    // Create physical memory with 5 frames
    PhysicalMemory pm(5);
    
    // Display initial frame information
    std::cout << "Initial Frame Information:" << std::endl;
    pm.display_frames_info();
    
    // Try to allocate a frame
    int frame_id = pm.find_free_frame();
    if (frame_id != -1) {
        std::cout << "Allocated Frame ID: " << frame_id << std::endl;
        // TODO: Mark the frame as used and update reference count
    } else {
        std::cout << "No free frames available!" << std::endl;
    }
    
    return 0;
} 