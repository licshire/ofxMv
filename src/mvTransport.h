#pragma once
#include "ofMain.h"
#include "mvDm365.h"
#include "ofxGui.h"

enum playbackMode {
    PLAYBACK_MODE_FORWARD = 0,
    PLAYBACK_MODE_BACKWARD,
    PLAYBACK_MODE_PINGPONG,
    PLAYBACK_MODE_SCRUB,
    NUMBER_OF_PLAYBACK_MODES
};


class mvTransport {
private:
    mvDm365 * davinci;

     int currentFrameNumber;

    int startFrame;
    int endFrame;

    int targetFrameNumber;

    float interFrameCounter;

    bool currentPingPingDirectionIsForward;

    void incrementInterFrameCounter();

    void checkFrameNumberBoundary();
    void goForward();
    void goBackwards();
    void goPingPong();
    void goScrub();

    int playcount;

public:
    mvTransport();
    void setup(mvDm365 * _davinci);
    void seekTo(int newFrameNum);
    void update();

    void setPlaybackSpeed(float speed);
    void setPercentInSequence(int percent);
    void scrubForwardsOne();
    void scrubBackwardsOne();

    inline int getPlaycount() {
        return playcount;
    }

    inline int getCurrentFrame() {
        return currentFrameNumber;
    }

    ofParameterGroup parameters;
    ofParameter<int> playbackModeParam;
    ofParameter<float> playbackSpeedParam;
    ofParameter<float> playbackPosition;



};
