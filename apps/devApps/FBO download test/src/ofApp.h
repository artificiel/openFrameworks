#pragma once

#include "ofMain.h"
#include "ofxFastFboReader.h"

class ofApp : public ofBaseApp {

public:
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key) override;

    ofShader shader;
    ofPlanePrimitive plane;

    int mode { 1 };
    bool upload { false };
    ofxFastFboReader reader;
    ofFbo fbo;
    ofPixels pixels;
    ofImage image;
};
