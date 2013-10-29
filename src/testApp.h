#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "crate.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
  //Created functions
    void wreckingBallSetup();
    void wreckingBallDraw();
  
  //OF stuff
    ofImage background, wreckingball;
  
  //BOX2D stuff
    ofxBox2d box2dWorld;			  //	the box2d world
  
  //vector of crate objects
    vector <crate*> crates;
  
  //wrecking ball
    ofxBox2dJoint chain;
    ofxBox2dRect anchor;
    ofxBox2dCircle ball;

};
