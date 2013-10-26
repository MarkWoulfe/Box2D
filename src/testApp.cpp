#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  background.loadImage("images/bg.jpg");
  
  //BOX2D stuff
  box2dWorld.init();
	box2dWorld.setGravity(0, 10);
	box2dWorld.createBounds();
	box2dWorld.setFPS(60.0);
	//box2d.registerGrabbing();
  
}

//--------------------------------------------------------------
void testApp::update(){
  
  box2dWorld.update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  background.draw(0,0);
  
  for(int i=0; i<crates.size(); i++) {
    crates[i]->draw();
  }
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
  vector<crate*>::iterator it = crates.begin();
  for(; it != crates.end();){
    delete *it;
    it = crates.erase(it);
  }
   
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  
  crate *newCrate = new crate(mouseX,mouseY,box2dWorld);
  
  crates.push_back(newCrate);
  
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}