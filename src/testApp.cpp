#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_NOTICE);
  
  //initialise our wreckingball variables
  anchorxPos = wreckingBallxPos = 425;
  anchoryPos = 100;
  anchorSize = 25;
  chainLength = 375;
  wreckingBallyPos = anchoryPos + chainLength;
  wreckingBallSize = 30;
  
  //specify values for our crates
  crateTowerWidth = 5;
  crateTowerxPos = 650;
  
  //load in images
  background.loadImage("images/bg.jpg");
  wreckingball.loadImage("images/wreckingball.png");
  craneArm.loadImage("images/crane.png");
  
  //set up the world
  box2dWorld.init();
	box2dWorld.setGravity(0, 10);
	box2dWorld.createBounds();
	box2dWorld.setFPS(30.0);
  
  //set up the crates and wrecking ball
  wreckingBallSetup();
  crateBuilderTower(crateTowerWidth,crateTowerxPos);
  
  // register the listener so that we get the events
	ofAddListener(box2dWorld.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2dWorld.contactEndEvents, this, &testApp::contactEnd);
  
  //sound
  sound.loadSound("sfx/1.wav");
  sound.setMultiPlay(true);
  sound.setLoop(false);
  
  //GUI
  guiDraw();
  
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
void testApp::guiDraw(){
  
  //create a GUI with a title, some text, a slider and a button
  guiWidth = 310;
  guixPos = ofGetWidth() - guiWidth;
  gui = new ofxUISuperCanvas("Menu - 'M' to toggle", guixPos, 0, guiWidth, 100, OFX_UI_FONT_MEDIUM);
  gui->toggleMinified();
  gui->addSpacer();
  gui->addTextArea("Instructions", "Set a new width and spawn a new tower with the slider and button below");
  gui->addSpacer();
  gui->addSlider("Width", 2, 8, &crateTowerWidth,guiWidth*0.5,8,0,100);
  gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
  gui->addButton("New Tower", false);
  gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
  gui->addSpacer();
  gui->addLabel("Control label", "Controls");
  gui->addSpacer();
  gui->addTextArea("controls", "M  - toggle the menu on/off");
  gui->addTextArea("controls2", "W - shorten the wrecking ball chain");
  gui->addTextArea("controls3", "S  - lengthen the wrecking ball chain");
  gui->addTextArea("controls4", "A  - pull the wrecking ball backwards (hold)");
  ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
  
}
//--------------------------------------------------------------
void testApp::crateBuilderTower(int height, int pos){
  
  //create a pyramid of triangles with some random positioning
  int size = 25-height;
  
  for (int i=0;i < height; i++){
    for (int j=0; j < height*2; j++ ){
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
  
  //joint
  ofPushStyle();
  ofSetColor(165,127,45);
  glLineWidth(3);
  chain.draw();
  ofPopStyle();
  
  //ball/circle
  ofPushMatrix();
  ofTranslate(ball.getPosition().x,ball.getPosition().y);
  wreckingball.draw(-ball.getRadius(),-ball.getRadius());
  ofPopMatrix();
  
  //craneArm
  ofPushMatrix();
  ofTranslate(anchor.getPosition().x,anchor.getPosition().y);
  ofRotate(75);
  craneArm.draw(-anchor.getWidth(),-anchor.getHeight()+10);
  ofPopMatrix();
  
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
  //check if the new tower button has been pressed, then reset the scene with the new tower
  if(e.widget->getName() == "New Tower")
  {
    ofxUIButton *button = (ofxUIButton *) e.widget;
    if (button->getValue()){
    //delete all crates (code taken from following link - http://www.openframeworks.cc/tutorials/c++%20concepts/001_stl_vectors_basic.html)
    vector<crate*>::iterator it = crates.begin();
    for(; it != crates.end();){
      delete *it;
      it = crates.erase(it);
    }
    //reset the world
    ball.setPosition(wreckingBallxPos, wreckingBallyPos);
    crateBuilderTower(crateTowerWidth,crateTowerxPos);
    box2dWorld.setGravity(0,10);
    }
  }
}
//--------------------------------------------------------------
void testApp::exit()
{
  delete gui;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
  //set a force to our vector
  wreckingBallForce.set(20000, 0);
  
  //move the wrecking ball left
  if (key == 'a'){
    ball.addForce(-wreckingBallForce, 1);
  }
 
  //reset gravity
  if (key == 'g'){
    box2dWorld.setGravity(-box2dWorld.getGravity());
  }
  
  if (key == 'm'){
    gui->toggleMinified();
  }
  
  //wrecking ball movement, move it up and down within reason
  if (key == 'w'){
    if(chainLength > wreckingBallSize*3){
      chain.setLength(chainLength-=wreckingBallSize);
      if(ball.isSleeping()) ball.setPosition(ball.getPosition().x, ball.getPosition().y-50);
    }
  }
  
  if (key == 's'){
    if(chainLength < (ofGetHeight()-anchoryPos)-wreckingBallSize*3){
      chain.setLength(chainLength+=wreckingBallSize);
      if(ball.isSleeping()) ball.setPosition(ball.getPosition().x, ball.getPosition().y+50);
    }
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