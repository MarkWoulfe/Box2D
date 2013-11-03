//
//  crate.h
//  Box2DFun
//
//  Created by Mark Woulfe on 20/10/2013.
//
//

#ifndef Box2DFun_crate_h
#define Box2DFun_crate_h

#include "ofMain.h"
#include "ofxBox2d.h"

class crate {
  
public:
  
  void draw();
  void* getData();
  void setData(void* data);
  
  crate(float x,float y, short crateSize, ofxBox2d &world);
  ~crate();
  
private:

  ofxBox2dRect		box;
  ofImage         crate_image;
  
  float x;
  float y;
  short crateSize;
  
};

#endif
