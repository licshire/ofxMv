#include "ofxMv.h"

ofxMv::ofxMv() {
}

void ofxMv::setup(string filename, int widthInMB, int heightInMB) {
    d.setup(filename, widthInMB, heightInMB);
    t.setup(&d);
    m.setup(&d);
    parameters.add(t.parameters);
}

void ofxMv::update() {
    t.update();
    m.update();
}

void ofxMv::draw() {
    m.draw();
}
