#pragma once
#include "ofMain.h"
#include "mvDm365.h"
#include "ofxGui.h"

#include <cmath>
#include <vector>

class mvMesh {
private:
    mvDm365 * d;
    ofMesh  faceMesh;

    ofVec3f translation;
    ofVec2f scale;
    float rotation;

public:
    mvMesh();
    void setup(mvDm365* _davinci);
    void update();
    void draw();

    void setTranslati
};
