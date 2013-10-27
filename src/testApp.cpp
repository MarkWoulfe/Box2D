#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  background.loadImage("images/bg.jpg");
  wreckingball.loadImage("images/wreckingball.png");
  
  //BOX2D stuff
  box2dWorld.init();
	box2dWorld.setGravity(0, 10);
	box2dWorld.createBounds();
	box2dWorld.setFPS(30.0);
	box2dWorld.registerGrabbing();
  
  anchor.setup(box2dWorld.getWorld(), 250, 100, 20, 20);
  ball.setPhysics(100.0, 0.1, 0.5);
  ball.setup(box2dWorld.getWorld(), 250, 300, 30);
  chain.setup(box2dWorld.getWorld(), anchor.body, ball.body);
  chain.setLength(400);
  
}

//--------------------------------------------------------------
void testApp::update(){
  
  box2dWorld.update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  background.draw(0,0);
  
  ofPushMatrix();
  ofTranslate(anchor.getPosition().x,anchor.getPosition().y);
  ofPushStyle();
  ofFill();
  ofSetColor(175, 175, 175);
  ofRect(-anchor.getWidth(), -anchor.getHeight(), 40, 525);
  ofPopStyle();
  ofPopMatrix();
  
  for(int i=0; i<crates.size(); i++) {
    crates[i]->draw();
  }
  
  //ofSetHexColor(0xffffff);
  
  ofPushStyle();
  ofFill();
  ofSetColor(128, 128, 128);
  chain.draw();
  ofPopStyle();
  
  ofPushMatrix();
  ofTranslate(ball.getPosition().x,ball.getPosition().y);
  ofRotate(ball.getRotation());
  ofLog() << ball.getRotation();
  wreckingball.draw(-ball.getRadius(),-ball.getRadius());
  ofPopMatrix();
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
  if (key == 'r'){
    vector<crate*>::iterator it = crates.begin();
    for(; it != crates.end();){
      delete *it;
      it = crates.erase(it);
    }
    
    ball.setPosition(250, 300);
    ball.setRotation(-ball.getRotation()); // doesnt work

  }
  
  if (key== 'c'){
    crate *newCrate = new crate(mouseX,mouseY,box2dWorld);
    crates.push_back(newCrate);
  }
  
  /* movement stuff
  if (key == 'd'){
    anchor.setPosition(anchor.getPosition().x+25, anchor.getPosition().y);
  }
  
  if (key == 'a'){
    anchor.setPosition(anchor.getPosition().x-25, anchor.getPosition().y);
  }
  */
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