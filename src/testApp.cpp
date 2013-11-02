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
  
  wreckingBallSetup();
  crateBuilderTriangle(6,400);
  
}
//--------------------------------------------------------------
void testApp::update(){
  
  box2dWorld.update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  background.draw(0,0);
  
  wreckingBallDraw();
  
  crateDraw();
  
}
//--------------------------------------------------------------
void testApp::crateBuilderTriangle(int amount, int pos){
  
  int tempAmount = amount;
  
  for (int i=0;i < amount; i++){
    for (int j=0; j < tempAmount; j++ ){
    crate *newCrate = new crate(pos+ofRandom(i*50,i*60)+(j*25),575-j*50,box2dWorld);
    crates.push_back(newCrate);
    }
    tempAmount--;
  }
  
}
//--------------------------------------------------------------
void testApp::crateDraw(){
  
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
  ball.setup(box2dWorld.getWorld(), 250, 500, 30);
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
  //ignore rotation, not necessarily needed
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
    ball.setPosition(250, 500);
    crateBuilderTriangle(6,400);
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