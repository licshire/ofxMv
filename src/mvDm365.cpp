#include "mvDm365.h"

mvDm365::mvDm365() {
}

void mvDm365::setup(string filename) {
    frameDataFile.open(filename.c_str(), ios::binary | ios::ate);
    fileSize = frameDataFile.tellg();
    frameDataFile.close();

    frameDataFile.open(filename.c_str(), ios::in | ios::binary );
    loadFrame(0);
}

void mvDm365::loadFrame(int frameNum) {
    long seekTo = frameNum * sizeof(frame);
    frameDataFile.seekg(seekTo);
    frameDataFile.read(buffer.char_buffer, sizeof(frame));

}


