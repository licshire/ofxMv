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

    inline void moveTo(float x, float y, float z) { translation.set(x,y,z); }
    inline void moveTo(ofVec3f moveToHere) { translation.set(moveToHere.x, moveToHere.y, moveToHere.z); }
    inline void setScale(float x, float y) { scale.set(x,y); }
    inline void setScale(ofVec2f scl) { scale.set(scl.x,scl.y); }
    inline void setRot(float rot) { rotation = rot; }
  };
