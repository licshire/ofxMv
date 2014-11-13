#include "mvDm365.h"

mvDm365::mvDm365() {
}

void mvDm365::setup(string filename, int widthInMB, int heightInMB) {
    frame_width_in_mb = widthInMB;
    frame_height_in_mb = heightInMB;

    frameDataFile.open(filename.c_str(), ios::binary | ios::ate);
    fileSize = frameDataFile.tellg();
    frameDataFile.close();
    frameDataFile.open(filename.c_str(), ios::in | ios::binary );
    loadFrame(0);
}

void mvDm365::loadFrame(int frameNum) {
    long seekTo = frameNum * getSizeOfFrame();
    frameDataFile.seekg(seekTo);
    frameDataFile.read(buffer.char_buffer, getSizeOfFrame());

}

//get mvDm365 stuff
int mvDm365::getMvX(int x, int y) {
    return buffer.current_frame.vector_field[xyToIndex(x, y)].MVx;
}

int mvDm365::getMvY(int x, int y) {
    return buffer.current_frame.vector_field[xyToIndex(x, y)].MVy;
}

int mvDm365::getSAD(int x, int y) {
    return buffer.current_frame.vector_field[xyToIndex(x, y)].SAD;
}

ofVec2f mvDm365::getVec2f(int x, int y) {
    ofVec2f mv(getMvX(x,y),getMvX(x,y));
    return mv;
}

