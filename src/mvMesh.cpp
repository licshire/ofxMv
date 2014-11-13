#include "mvMesh.h"

mvMesh::mvMesh() {
}

void mvMesh::setup(mvDm365 * _davinci) {
    d = _davinci;

    for (int y = 0; y < d->getFrameHeight(); y ++) {
        for (int x = 0; x < d->getFrameWidth(); x ++ ) {
            int x1 = x*d->mb_px_side + d->mb_px_midside;
            int y1 = y*d->mb_px_side + d->mb_px_midside;
            ofVec3f pos(x1,y1,0);
            faceMesh.addVertex(pos);
        }
    }

    for (int y = 1; y < d->getFrameHeight(); y ++ ) {
        for ( int x = 1; x < d->getFrameWidth(); x ++) {
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

void mvMesh::translate(int x, int y, int scale) {

}

void mvMesh::update() {
    //faceMesh.clear();

    for (int y = 0; y < d->getFrameHeight(); y ++) {
        for (int x = 0; x < d->getFrameWidth(); x ++ ) {

            ofVec3f mv(d->getMvX(x,y), d->getMvY(x,y), -d->getVec2f(x,y).length());
            ofVec3f centPosition(x*d->mb_px_side + d->mb_px_midside, y*d->mb_px_side + d->mb_px_midside, 0);

            ofVec3f oldPosition;
            oldPosition = faceMesh.getVertex(d->xyToIndex(x,y));
            ofVec3f goalPosition;
            goalPosition = centPosition+mv;

            ofVec3f newPosition;
            newPosition = oldPosition;
            newPosition.interpolate(goalPosition, 0.1);

            faceMesh.getVertices()[d->xyToIndex(x,y)].set(newPosition);

        }
    }
}

void mvMesh::draw() {
    ofSetColor(255,255,255);
    ofSetLineWidth(.5);

    faceMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    ofFill();
    faceMesh.drawWireframe();
}
