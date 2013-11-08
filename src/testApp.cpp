#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  //initialise our wreckingball variables
  anchorxPos = wreckingBallxPos = 450;
  anchoryPos = 100;
  anchorSize = 20;
  wreckingBallyPos = 500;
  wreckingBallSize = 30;
  chainLength = wreckingBallyPos - anchoryPos;
  
  //specify values for our crates
  crateTowerHeight = 8;
  crateTowerxPos = 600;
  
  //load in images
  background.loadImage("images/bg.jpg");
  wreckingball.loadImage("images/wreckingball.png");
  
  //set up the world
  box2dWorld.init();
	box2dWorld.setGravity(0, 10);
	box2dWorld.createBounds();
	box2dWorld.setFPS(30.0);
  
  //set up the crates and wrecking ball
  wreckingBallSetup();
  crateBuilderTower(crateTowerHeight,crateTowerxPos);
  
  // register the listener so that we get the events
	ofAddListener(box2dWorld.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2dWorld.contactEndEvents, this, &testApp::contactEnd);
  
  //sound
  sound.loadSound("sfx/1.wav");
  sound.setMultiPlay(true);
  sound.setLoop(false);
  
}
//following two functions taken from a sound example, as the wrecking ball
//object is the only one we give sounddata to, we don't need half of the code
//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
	//if(e.a != NULL && e.b != NULL) {
			
			//SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
			SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
			
			/*if(aData) {
				aData->bHit = true;
        sound.play();
			}*/
			
			if(bData) {
				bData->bHit = true;
				sound.play();
			}
   //}
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
	//if(e.a != NULL && e.b != NULL) {
		
		//SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
		SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
		
		/*if(aData) {
			aData->bHit = false;
		}*/
		
		if(bData) {
			bData->bHit = false;
		}
	//}
}

//--------------------------------------------------------------
void testApp::update(){
  
  //update the world
  box2dWorld.update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  //draw everything
  background.draw(0,0);
  
  wreckingBallDraw();
  
  crateDraw();
  
}
//--------------------------------------------------------------
void testApp::crateBuilderTower(int height, int pos){
  
  //create a pyramid of triangles with some random positioning
  int size = 30-height;
  
  for (int i=0;i < height; i++){
    for (int j=0; j < height*1.5; j++ ){
    crate *newCrate = new crate(pos+ofRandom(i*(size*2),i*(size*2.5)),ofGetHeight()-size-j*(size*2), size, box2dWorld);
    crates.push_back(newCrate);
    }
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
  anchor.setup(box2dWorld.getWorld(), anchorxPos, anchoryPos, anchorSize, anchorSize);
  ball.setPhysics(100.0, 0.1, 0.5);
  ball.setup(box2dWorld.getWorld(), wreckingBallxPos, wreckingBallyPos, wreckingBallSize);
  
  //sound
  ball.setData(new SoundData());
  
  chain.setup(box2dWorld.getWorld(), anchor.body, ball.body);
  chain.setLength(chainLength);
  
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
  wreckingball.draw(-ball.getRadius(),-ball.getRadius());
  ofPopMatrix();
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
  //delete all crates (code taken from following link - http://www.openframeworks.cc/tutorials/c++%20concepts/001_stl_vectors_basic.html)
  if (key == 'r'){
    vector<crate*>::iterator it = crates.begin();
    for(; it != crates.end();){
      delete *it;
      it = crates.erase(it);
    }
    //reset the world
    ball.setPosition(wreckingBallxPos, wreckingBallyPos);
    crateBuilderTower(crateTowerHeight,crateTowerxPos);
  }
  
  //set a force to our vector
  wreckingBallForce.set(10000, 0 );
  
  //move the wrecking ball left
  if (key == 'a'){
    ball.addForce(-wreckingBallForce, 1);
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