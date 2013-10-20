#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  background.loadImage("images/bg.jpg");
  crate.loadImage("images/crate.png");
  
  crateSize = 25;
  
  //BOX2D stuff
  box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(60.0);
	//box2d.registerGrabbing();
  
}

//--------------------------------------------------------------
void testApp::update(){
  box2d.update();
}

//--------------------------------------------------------------
void testApp::draw(){
  
  background.draw(0,0);
  
  ofLog() << crates.size();
  
    for(int i=0; i<crates.size(); i++) {
      ofPushMatrix();
      ofTranslate(boxes[i].getPosition().x,boxes[i].getPosition().y);
      ofRotate(boxes[i].getRotation());
      crates[i].draw(-boxes[i].getWidth(),-boxes[i].getHeight());
      //boxes[i].draw();
      ofPopMatrix();
    }

  // draw the ground // makes openframeworks drawing weird for some reason
	  //box2d.drawGround();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
 if (key == 'r'){
    for(int i=0; i<boxes.size(); i++) {
      boxes[i].destroy();
      //boxes.erase(i);
    }
    for(int i=0; i<crates.size(); i++) {
      crates[i].clear();
      //crates.erase(i);
    }
   crates.erase(crates.begin(),crates.end());
   boxes.erase(boxes.begin(),boxes.end());
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

  ofxBox2dRect rect;
  rect.setPhysics(5.0, 0.23, 0.5);
  rect.setup(box2d.getWorld(), mouseX, mouseY, crateSize, crateSize);
  boxes.push_back(rect);
  
  crates.push_back(crate);
  
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