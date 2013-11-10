//
//  crate.h
//  Box2DFun
//
//  Created by Mark Woulfe on 20/10/2013.
//
// Our crate class aka a box2d rectangle with an image drawn on top

#ifndef Box2DFun_crate_h
#define Box2DFun_crate_h

#include "ofMain.h"
#include "ofxBox2d.h"

class crate {
  
public:
  
  void draw();
  
  crate(float x,float y, short crateSize, ofxBox2d &world);
  ~crate();
  
private:

  //set up our crate with a box2d rectangle, an image and a few other variables
  ofxBox2dRect		box;
  ofImage         crate_image;
  
  float x;
  float y;
  short crateSize;
  
};

#endif
