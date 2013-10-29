#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  //load in images
  background.loadImage("images/bg.jpg");
  wreckingball.loadImage("images/wreckingball.png");
  
  //set up the world
  box2dWorld.init();
	box2dWorld.setGravity(0, 10);
	box2dWorld.createBounds();
	box2dWorld.setFPS(30.0);
	//box2dWorld.registerGrabbing();
  
  wreckingBallSetup();
  
}
//--------------------------------------------------------------
void testApp::update(){
  
  box2dWorld.update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  background.draw(0,0);
  
  wreckingBallDraw();
  
  //draw all the crates
  for(int i=0; i<crates.size(); i++) {
    crates[i]->draw();
  }
  
}
//--------------------------------------------------------------
void testApp::wreckingBallSetup(){
  
  //set up what makes the wrecking ball, a stationary anchor, a box2d circle and a joint combining them
  anchor.setup(box2dWorld.getWorld(), 250, 100, 20, 20);
  ball.setPhysics(1000.0, 0.1, 0.5);
  ball.setup(box2dWorld.getWorld(), 250, 300, 30);
  chain.setup(box2dWorld.getWorld(), anchor.body, ball.body);
  chain.setLength(400);
  
}
//--------------------------------------------------------------
void testApp::wreckingBallDraw(){
  
  //anchor
  ofPushMatrix();
  ofTranslate(anchor.getPosition().x,anchor.getPosition().y);
  ofPushStyle();
  ofFill();
  ofSetColor(175, 175, 175);
  ofRect(-anchor.getWidth(), -anchor.getHeight(), 40, 525);
  ofPopStyle();
  ofPopMatrix();
  
  //joint
  ofPushStyle();
  ofFill();
  ofSetColor(128, 128, 128);
  chain.draw();
  ofPopStyle();
  
  //ball/circle
  ofPushMatrix();
  ofTranslate(ball.getPosition().x,ball.getPosition().y);
  //ofRotate(ball.getRotation());
  //cofLog() << ball.getRotation();
  wreckingball.draw(-ball.getRadius(),-ball.getRadius());
  ofPopMatrix();
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
  //delete all crates
  if (key == 'r'){
    vector<crate*>::iterator it = crates.begin();
    for(; it != crates.end();){
      delete *it;
      it = crates.erase(it);
    }
    ball.setPosition(250, 300);
  }
  
  //create a new crate at the mouse position
  if (key== 'c'){
    crate *newCrate = new crate(mouseX,mouseY,box2dWorld);
    crates.push_back(newCrate);
  }
  
  //create a directional vector
  ofVec2f v1;
  v1.set(-100000, 0 );
  
  
  //move the wrecking ball left and right with that force
  if (key == 'a'){
    ball.addForce(v1, 1);
  }
  
  if (key == 'd'){
    ball.addForce(-v1, 1);
  }
 
  //reset gravity
  if (key == 'g'){
    box2dWorld.setGravity(-box2dWorld.getGravity());
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