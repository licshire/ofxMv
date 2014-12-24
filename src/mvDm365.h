#pragma once
#include "ofMain.h"
#include <fstream>

#define WIDTH_MB 44
#define HEIGHT_MB 30
#define TOTAL_MB WIDTH_MB*HEIGHT_MB

struct motion_vector {
    int16_t MVx;
    int16_t MVy;
    uint32_t SAD;
};

struct frame {
    motion_vector vector_field[TOTAL_MB];
};

union frame_buffer {
    char char_buffer[TOTAL_MB * sizeof(motion_vector)];
    struct frame current_frame;
};

class mvDm365 {
private:
    ifstream frameDataFile;
    frame_buffer buffer;

    int fileSize; // in bytes
    int frame_width_in_mb = WIDTH_MB;
    int frame_height_in_mb = HEIGHT_MB;

public:
    const int mb_px_side = 16;

    mvDm365();
    void loadFrame(int frameNum);
    void setup(string filename);

    //get motion vectors
    inline int getMvX(int x, int y) {       return buffer.current_frame.vector_field[xyToIndex(x, y)].MVx;  }
    inline int getMvY(int x, int y) {       return buffer.current_frame.vector_field[xyToIndex(x, y)].MVy;  }
    inline int getSAD(int x, int y) {       return buffer.current_frame.vector_field[xyToIndex(x, y)].SAD;  }
    inline ofVec2f getVec2f(int x, int y) { ofVec2f mv(getMvX(x,y),getMvX(x,y));
                                            return mv;}

    inline int getMvX(int index) {          return getMvX(indexToX(index), indexToY(index));    }
    inline int getMvY(int index) {          return getMvY(indexToX(index), indexToY(index));    }
    inline int getSAD(int index) {          return getSAD(indexToX(index), indexToY(index));    }
    inline ofVec2f getVec2f(int index) {    return getVec2f(indexToX(index), indexToY(index)); }

    //get dimensions
    inline int getFrameWidthMb() {          return frame_width_in_mb;}
    inline int getFrameHeightMb() {         return frame_height_in_mb;}
    inline int getFrameWidthPx() {          return frame_width_in_mb * mb_px_side;}
    inline int getFrameHeightPx() {         return frame_height_in_mb * mb_px_side;}

    inline int getNumberOfFrames() {        return fileSize/sizeof(frame);}

    inline int xyToIndex(int x,int y)   {   return y*getFrameWidthMb() + x;}
    inline int indexToX(int index)      {   return index % getFrameWidthMb();}
    inline int indexToY(int index)      {   return (index - indexToX(index)) / getFrameWidthMb();}


};

