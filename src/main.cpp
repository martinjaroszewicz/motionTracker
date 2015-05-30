//
//  main.cpp
//  motionTracker
//
//  Created by Martin Jaroszewicz on 5/18/15.
//  Copyright (c) 2015 com.jaroszewicz. All rights reserved.
//
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(900,600,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
