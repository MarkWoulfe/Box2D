#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "crate.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{
  //all default OF functions
	public:
		void setup();
		void update();
		void draw();
    void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void guiEvent(ofxUIEventArgs &e);
  
  //Created functions
  
    //functions to tidy our wrecking ball and crate tower code away
    void wreckingBallSetup();
    void wreckingBallDraw();
    void crateBuilderTower(int height, int pos);
    void crateDraw();
  
    //a function for drawing our GUI
    void guiDraw();
  
  //Image stuff
    ofImage background, wreckingball, craneArm;
  
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
    short crateTowerxPos;
    float crateTowerWidth;
  
  //Sound
  
  //a struct used in the sound detection with a boolean for detecting if a collision has happened
    struct SoundData {
      bool bHit = false;
    };
  
  //this is the function for contacts
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
  
	//when the ball hits we play this sound
    ofSoundPlayer  sound;
  
  //GUI
    ofxUISuperCanvas *gui;
    short guiWidth, guixPos;
  

};
