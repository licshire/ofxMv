#include "mvMesh.h"

mvMesh::mvMesh() {

}

void mvMesh::setup(mvDm365 * _davinci) {
    d = _davinci;

    translation.set(0,0,0);
    scale.set(d->mb_px_side,d->mb_px_side);
    rotation = 0;

    for (int y = 0; y < d->getFrameHeightMb(); y ++) {
        for (int x = 0; x < d->getFrameWidthMb(); x ++ ) {
            float x1 = x*scale.x;
            float y1 = y*scale.y;
            ofVec3f pos(x1,y1,0);
            faceMesh.addVertex(pos);
        }
    }

    for (int y = 1; y < d->getFrameHeightMb(); y ++ ) {
        for ( int x = 1; x < d->getFrameWidthMb(); x ++) {
            faceMesh.addIndex(d->xyToIndex(x,y));
            faceMesh.addIndex(d->xyToIndex(x,y-1));
            faceMesh.addIndex(d->xyToIndex(x-1,y-1));

            faceMesh.addIndex(d->xyToIndex(x,y-1));
            faceMesh.addIndex(d->xyToIndex(x-1,y-1));
            faceMesh.addIndex(d->xyToIndex(x-1,y));

            faceMesh.addIndex(d->xyToIndex(x-1,y-1));
            faceMesh.addIndex(d->xyToIndex(x-1,y));
            faceMesh.addIndex(d->xyToIndex(x,y));

            faceMesh.addIndex(d->xyToIndex(x-1,y));
            faceMesh.addIndex(d->xyToIndex(x,y));
            faceMesh.addIndex(d->xyToIndex(x,y-1));

        }
    }

}

void mvMesh::update() {
    for (int y = 0; y < d->getFrameHeightMb(); y ++) {
        for (int x = 0; x < d->getFrameWidthMb(); x ++ ) {
            ofVec2f originalVector = d->getVec2f(x,y);
            originalVector.set((originalVector.x/d->mb_px_side)*scale.x, (originalVector.y/d->mb_px_midside)*scale.y);

            ofVec3f mv(originalVector.x,originalVector.x, originalVector.length());
            ofVec3f originalPosition(x*scale.x, y*scale.y, 0);

            ofVec3f oldPosition;
            oldPosition = faceMesh.getVertex(d->xyToIndex(x,y));
            ofVec3f goalPosition;
            goalPosition = originalPosition+mv;

            ofVec3f newPosition;
            newPosition = oldPosition;
            newPosition.interpolate(goalPosition, 0.1);

            faceMesh.getVertices()[d->xyToIndex(x,y)].set(newPosition);

        }
    }
}

void mvMesh::draw() {
    ofPushMatrix();
    ofTranslate(translation);
    ofRotateX(rotation);
    faceMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    faceMesh.drawWireframe();
    ofPopMatrix();
}
