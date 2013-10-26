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
  
  //BOX2D stuff
    ofxBox2d						box2dWorld;			  //	the box2d world

  
  //OF stuff
    ofImage background;
  
  
  //vector of crate objects
  vector <crate> crates;

};
