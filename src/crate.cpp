//
//  crate.c
//  Box2DFun
//
//  Created by Mark Woulfe on 20/10/2013.
//
//

#include "crate.h"

crate::crate(float _x, float _y, ofxBox2d &world/*, int _crateSize*/){
  
  x = _x;
  y = _y;
  crateSize = 25;
  crate_image.loadImage("images/crate.png");
  box.setPhysics(5.0, 0.23, 0.5);
  box.setup(world.getWorld(), x, y, crateSize, crateSize);
  
}

void crate::update(){
}

void crate::draw(){
  
  ofPushMatrix();
  ofTranslate(box.getPosition().x,box.getPosition().y);
  ofRotate(box.getRotation());
  crate_image.draw(-box.getWidth(),-box.getHeight());
  ofPopMatrix();
  
}

void crate::destroy(){
  
  box.destroy();
  crate_image.clear();
  
}