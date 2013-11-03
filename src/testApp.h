#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "crate.h"

#define N_SOUNDS 2

class SoundData {
public:
  int	 soundID;
  bool bHit;
};

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
    void crateBuilderPyramid(int height, int pos, int size);
    void crateDraw();
  
  //OF stuff
    ofImage background, wreckingball;
  
  //BOX2D stuff
    ofxBox2d box2dWorld;
  
  //vector of pointers to crate objects
    vector <crate*> crates;
  
  //wrecking ball
    ofxBox2dJoint chain;
    ofxBox2dRect anchor;
    ofxBox2dCircle ball;
    ofVec2f wreckingBallForce;
    short anchorxPos, anchoryPos, anchorSize;
    short wreckingBallxPos, wreckingBallyPos, wreckingBallSize;
    short chainLength;
  
  //crate formation
    short cratePyramidHeight, cratePyramidxPos, crateSize;
  
  //Sound
  
  // this is the function for contacts
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
  
	// when the ball hits we play this sound
    ofSoundPlayer  sound[N_SOUNDS];
  

};
