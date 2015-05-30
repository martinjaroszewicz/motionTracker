//
//  main.cpp
//  motionTracker
//
//  Created by Martin Jaroszewicz on 5/18/15.
//  Copyright (c) 2015 com.jaroszewicz. All rights reserved.
//
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <ofxOsc.h>

#define PORT 8000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVideoGrabber movie;
    ofxCvColorImage rgb,hsb;
    ofxCvGrayscaleImage hue,sat,bri,filtered;
    ofxCvContourFinder contours;
    ofxOscSender *sender;
    
    int w,h;
    int findHue;
    
};
