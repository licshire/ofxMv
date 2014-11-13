#pragma once
#include "ofMain.h"
#include <fstream>

///todo dynamically allocate for structs
#define TOTAL_MB 44*33
#define MB_STRUCT_SIZE 8


///todo, convert this into an interface

struct motion_vector {
    int16_t MVx;
    int16_t MVy;
    uint32_t SAD;
};

struct frame {
    motion_vector vector_field[TOTAL_MB];
};

union frame_buffer {
    char char_buffer[TOTAL_MB * MB_STRUCT_SIZE];
    struct frame current_frame;
};

class mvDm365 {
private:
    ifstream frameDataFile;
    frame_buffer buffer;

    int fileSize; // in bytes
    int frame_width_in_mb;
    int frame_height_in_mb;

public:
    const int mb_px_side = 16;
    const int mb_px_midside = mb_px_side/2;

    mvDm365();
    void loadFrame(int frameNum);
    void setup(string filename, int widthInMB, int heightInMB);

    int getMvX(int x, int y);
    int getMvX(int index);
    int getMvY(int x, int y);
    int getMvY(int index);
    int getSAD(int x, int y);
    int getSAD(int index);
    ofVec2f getVec2f(int x, int y);

    inline int getFileSize() {
        return fileSize;
    }
    inline int getFrameWidthMb() {
        return frame_width_in_mb;
    }
    inline int getFrameHeightMb() {
        return frame_height_in_mb;
    }
    inline int getFrameWidthPx() {
        return frame_width_in_mb * mb_px_side;
    }
    inline int getFrameHeightPx() {
        return frame_height_in_mb * mb_px_side;
    }

    inline int getNumberOfMacroblocksInFrame() {
        return frame_width_in_mb * frame_height_in_mb;
    }

    inline int getSizeOfMotionVector() {
        return 8;//16+16+32 bits = 64 bits = 8 bytes
    }

    inline int getSizeOfFrame() {
        return getSizeOfMotionVector()*getNumberOfMacroblocksInFrame();
    }

    inline int getNumberOfFrames() {
        return fileSize / getSizeOfFrame();
    }
    // play rewind scrub reset (should be in framecontrol handler)

    inline int xyToIndex(int x,int y)   {
        return y*getFrameWidthMb() + x;
    }
    inline int indexToX(int index)      {
        return index % getFrameWidthMb();
    }
    inline int indexToY(int index)      {
        return (index - indexToX(index)) / getFrameWidthMb();
    }


};

