//
//  main.cpp
//  motionTracker
//
//  Created by Martin Jaroszewicz on 5/18/15.
//  Copyright (c) 2015 com.jaroszewicz. All rights reserved.
//
#include "ofApp.h"

int rectangles[5][4];
int indexRect;
bool startDrawing;
bool enterDrawing;

//--------------------------------------------------------------
void ofApp::setup(){
    indexRect = 0;
    startDrawing = false;
    enterDrawing = false;
    ofSetColor(255,0,0);
    ofSetFrameRate(60);
    ofNoFill();
    ofBackground(0,0,0);
    
    w = 320;
    h = 240;
    
    movie.initGrabber(w, h, true);
    
    //reserve memory for cv images
    rgb.allocate(w, h);
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filtered.allocate(w, h);
    
    sender = new ofxOscSender;
    sender->setup("localhost", PORT);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    movie.update();
    
    if (movie.isFrameNew()) {
        
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels(), w, h);
        
        //mirror horizontal
        rgb.mirror(false, true);
        
        //duplicate rgb
        hsb = rgb;
        
        //convert to hsb
        hsb.convertRgbToHsv();
        
        //store the three channels as grayscale images
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filtered.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue-5,findHue+5) ? 255 : 0;
        }
        
        filtered.flagImageChanged();
        //run the contour finder on the filtered image to find blobs with a certain hue
        contours.findContours(filtered, 50, w*h/2, 1, false);
    }
    
    for (int j=0; j<5; j++) {
        for (int i=0; i<contours.nBlobs; i++) {
            if (contours.blobs[i].centroid.x > rectangles[j][0] && contours.blobs[i].centroid.x < rectangles[j][2] + rectangles[j][0] && contours.blobs[i].centroid.y > rectangles[j][1] && contours.blobs[i].centroid.y < rectangles[j][3] + rectangles[j][1])
            {
                cout << j << endl;
                ofxOscMessage m;
                m.setAddress("/boxNumber");
                m.addIntArg(j);
                sender->sendMessage(m);
            }
            else {
                cout << "No contact" << endl;
                
            };
        };
    };
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    
    //draw all cv images
    rgb.draw(0,0);
    hsb.draw(640,0);
    hue.draw(0,240);
    sat.draw(320,240);
    bri.draw(640,240);
    filtered.draw(0,480);
    contours.draw(0,480);
    
    ofSetColor(255, 0, 0);
    ofFill();
    
    //draw red circles for found blobs
    
    for (int i=0; i<contours.nBlobs; i++) {
        ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 10);
        
    }
    if (startDrawing) {
        ofRect(rectangles[indexRect][0], rectangles[indexRect][1], mouseX - rectangles[indexRect][0], mouseY - rectangles[indexRect][1]);
    };
    
    if (enterDrawing or indexRect == 0){
        ofNoFill();
        for (int i = 0; i<5; i++) {
            ofRect(rectangles[i][0], rectangles[i][1], rectangles[i][2],rectangles[i][3]);
        };
    };
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key ;
    if (key == 13){ //return jkey
        enterDrawing = true;
        ofSetColor(255,0,0);
        indexRect++;
    };
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofSetColor(255, 255, 0);
    rectangles[indexRect][0]= x;
    rectangles[indexRect][1]= y;
    rectangles[indexRect][2]= x - rectangles[indexRect][0];
    rectangles[indexRect][3]= y - rectangles[indexRect][1];
    startDrawing = true;
    
    //movie
    //calculate local mouse x,y in image
    int mx = x % w;
    int my = y % h;
    
    //get hue value on mouse position
    findHue = hue.getPixels()[my*w+mx];
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    rectangles[indexRect][2]= x - rectangles[indexRect][0];
    rectangles[indexRect][3]= y - rectangles[indexRect][1];
    startDrawing = false;
    
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}



