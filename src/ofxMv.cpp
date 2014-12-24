#include "ofxMv.h"

ofxMv::ofxMv() {
}

void ofxMv::setup(string filename) {
    d.setup(filename);
    t.setup(&d);
    m.setup(&d);
    parameters = t.parameters;
}

void ofxMv::update() {
    t.update();
    m.update();
}

void ofxMv::draw() {
    m.draw();
}
