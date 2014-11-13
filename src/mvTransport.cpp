#include "mvTransport.h"

mvTransport::mvTransport() {
    parameters.setName("playback");

    currentFrameNumber = 0;
    targetFrameNumber = 0;
    currentPingPingDirectionIsForward = true;
    playcount = 0;

    interFrameCounter = 0;
}

void mvTransport::setup(mvDm365 *_davinci, int _startFrame, int _endFrame) {
    davinci = _davinci;
    startFrame = _startFrame;
    endFrame = _endFrame-1;
    currentFrameNumber = _startFrame;

    parameters.add(playbackPosition.set("position", currentFrameNumber, startFrame, endFrame));
    parameters.add(playbackSpeedParam.set("speed", 1, 0.001, 2));
    parameters.add(playbackModeParam.set("playback mode", PLAYBACK_MODE_FORWARD, 0, NUMBER_OF_PLAYBACK_MODES-1));

}

void mvTransport::update() {
    switch (playbackModeParam) {
    case PLAYBACK_MODE_FORWARD:
        playbackModeParam.setName("mode: forwards");
        goForward();
        playbackPosition.set("position", currentFrameNumber);
        break;
    case PLAYBACK_MODE_BACKWARD:
        playbackModeParam.setName("mode: backwards");
        goBackwards();
        playbackPosition.set("position", currentFrameNumber);
        break;
    case PLAYBACK_MODE_PINGPONG:
        playbackModeParam.setName("mode: ping pong");
        goPingPong();
        playbackPosition.set("position", currentFrameNumber);
        break;
    case PLAYBACK_MODE_SCRUB:
        playbackModeParam.setName("mode: manual");
        goScrub();
        playbackPosition.setName("position");
        targetFrameNumber = playbackPosition;
        break;
    }

}

void mvTransport::incrementInterFrameCounter() {
    float baseRate =  (15/ofGetFrameRate());
    interFrameCounter += playbackSpeedParam * baseRate;
}


void mvTransport::goForward() {

    incrementInterFrameCounter();
    float temp = interFrameCounter;
    while (temp >= 0) {
        temp -= 1;
        if (temp >= 0) {
            interFrameCounter = 0;
            currentFrameNumber++;
        }
    }
    checkFrameNumberBoundary();
    davinci->loadFrame(currentFrameNumber);

}

void mvTransport::goBackwards() {

    incrementInterFrameCounter();
    float temp = interFrameCounter;
    while (temp >= 0) {
        temp -= 1;
        if (temp >= 0) {
            interFrameCounter = 0;
            currentFrameNumber--;
        }
    }
    checkFrameNumberBoundary();
    davinci->loadFrame(currentFrameNumber);
}

void mvTransport::goPingPong() {
    if (currentPingPingDirectionIsForward) {
        goForward();
    } else {
        goBackwards();
    }
}

void mvTransport::checkFrameNumberBoundary() {
    switch (playbackModeParam) {
    case PLAYBACK_MODE_FORWARD:
        if (currentFrameNumber > endFrame) {
            playcount ++;
            currentFrameNumber = startFrame;
        }
        break;
    case PLAYBACK_MODE_BACKWARD:
        if (currentFrameNumber < startFrame) {
            playcount ++;
            currentFrameNumber = endFrame;
        }
        break;
    case PLAYBACK_MODE_PINGPONG:
        if (currentFrameNumber > endFrame) {
            currentFrameNumber = endFrame;
            currentPingPingDirectionIsForward = false;
        }
        if (currentFrameNumber < startFrame) {
            playcount++;
            currentFrameNumber = startFrame;
            currentPingPingDirectionIsForward = true;
        }
        break;
    case PLAYBACK_MODE_SCRUB:
        playcount = 0;
        if (currentFrameNumber > endFrame) {
            currentFrameNumber = endFrame;
        }
        if (currentFrameNumber < startFrame) {
            currentFrameNumber = startFrame;
        }
        break;
    }

}

void mvTransport::goScrub() {
    currentFrameNumber = currentFrameNumber + (targetFrameNumber - currentFrameNumber)/3;
    checkFrameNumberBoundary();
    davinci->loadFrame(currentFrameNumber);
}

void mvTransport::setPercentInSequence(int percent) {
    if (percent < 0 || percent > 100 ) throw std::invalid_argument( "010101001010010010 non percent value" );
    targetFrameNumber = ofMap(percent, 0, 100, startFrame, endFrame);
}

void mvTransport::scrubForwardsOne() {
    playbackPosition ++;
    currentFrameNumber = playbackPosition;
    targetFrameNumber = playbackPosition;
}

void mvTransport::scrubBackwardsOne() {
    playbackPosition --;
    currentFrameNumber = playbackPosition;
    targetFrameNumber = playbackPosition;
}



