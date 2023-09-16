#include "ofApp.h"

void ofApp::setup() {

    ofSetVerticalSync(false);
    ofSetWindowShape(1920, 1080);

    if (ofIsGLProgrammableRenderer()) {
        shader.load("shadersGL3/shader");
    } else {
        shader.load("shadersGL2/shader");
    }

    float planeScale = 0.75;
    int planeWidth = ofGetWidth() * planeScale;
    int planeHeight = ofGetHeight() * planeScale;
    int planeGridSize = 20;
    int planeColums = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;

    plane.set(planeWidth, planeHeight, planeColums, planeRows, OF_PRIMITIVE_TRIANGLES);

    fbo.allocate(1920, 1090, GL_RGBA, 0);
}

void ofApp::update() {
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofApp::draw() {

    float percentX = mouseX / (float)fbo.getWidth();
    percentX = ofClamp(percentX, 0, 1);

    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();

    ofPushMatrix();
    for (size_t i = 0; i < num_iters ; i++) {
        fbo.begin();
        shader.begin();

        // a lot of the time you have to pass in variables into the shader.
        // in this case we need to pass it the elapsed time for the sine wave animation.
        shader.setUniform1f("time", ofGetElapsedTimef());

        // translate plane into center screen.
        float tx = ofGetWidth() / 2;
        float ty = ofGetHeight() / 2;
        ofTranslate(tx+i*10, ty+i*10);

        // the mouse/touch Y position changes the rotation of the plane.
        float percentY = mouseY / (float)ofGetHeight();
        float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
        ofRotateDeg(rotation, 1, 0, 0);

        plane.drawWireframe();

        shader.end();
        fbo.end();

        fbo.draw(20, ofGetHeight()/4, 192, 108);

        if (mode == 1) {
            fbo.readToPixels(pixels);
        } else if (mode == 2) {
            fbo.readToPixelsNEW(pixels);
        } else if (mode == 3) {
            reader.readToPixels(fbo, pixels, OF_IMAGE_COLOR_ALPHA);
        }
    }
    ofPopMatrix();

    if (mode != 0) {
        if (upload) {
            image.setFromPixels(pixels);
            image.draw(0, 0, 1920, 1080);
        }
    }

    ofDrawBitmapStringHighlight("mode " + ofToString(mode), 20, 20);
    ofDrawBitmapStringHighlight("upload " + ofToString(upload), 20, 40);
    ofDrawBitmapStringHighlight("num iters " + ofToString(num_iters), 20, 60);

    ofDrawBitmapStringHighlight("adjust the numbers of iterations with <+/-> until the framerate is near 30fps", 20, ofGetHeight()/2);
    ofDrawBitmapStringHighlight("toggle the upload with <u> to view the actually-downloaded texture", 20, ofGetHeight()/2+30);

    ofDrawBitmapStringHighlight("fps " + ofToString(ofGetFrameRate()), 20, 90);
    ofDrawBitmapStringHighlight("0 = no download; 1 = old school; 2 = new school; 3 = ofxFastFboReader", 20, ofGetHeight() - 20);
    ofDrawBitmapStringHighlight("u = toggle upload", 20, ofGetHeight() - 40);
}

void ofApp::keyPressed(int key) {
    if (key == '0') mode = 0;
    if (key == '1') mode = 1;
    if (key == '2') mode = 2;
    if (key == '3') mode = 3;
    if (key == 'u') upload = !upload;
    if (key == '+') num_iters = ofClamp(num_iters+1, 1, 100);
    if (key == '-') num_iters = ofClamp(num_iters-1, 1, 100);

}
