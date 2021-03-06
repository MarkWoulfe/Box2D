//
//  crate.c
//  Box2DFun
//
//  Created by Mark Woulfe on 20/10/2013.
//
//

#include "crate.h"

crate::crate(float _x, float _y, short _crateSize, ofxBox2d &world){
  
  //get in all our values and set up our image to the correct scale then create our box and set some physics for it
  x = _x;
  y = _y;
  crateSize = _crateSize;
  crate_image.loadImage("images/crate.png");
  crate_image.resize(crateSize*2, crateSize*2);
  box.setPhysics(2.5, 0.23, 0.5);
  box.setup(world.getWorld(), x, y, crateSize, crateSize);
  
}

void crate::draw(){
  
  //draw the image and have it rotate as the box2d object rotates
  ofPushMatrix();
  ofTranslate(box.getPosition().x,box.getPosition().y);
  ofRotate(box.getRotation());
  crate_image.draw(-box.getWidth(),-box.getHeight());
  ofPopMatrix();
  
}

crate::~crate(){
  
  //destroy both the box2d object and clear the image
  box.destroy();
  crate_image.clear();
  
}