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
  
public: // place private functions or variables declarations here
  
  // methods, equivalent to specific functions of your class objects
  void update();  // update method, used to refresh your objects properties
  void draw();    // draw method, this where you'll do the object's drawing
  void destroy();
  
  // variables
  ofxBox2dRect		box;			  //	defalut box2d rects
  ofImage         crate_image;
  
  float x;      // position
  float y;
  int crateSize;
  
//public: // place public functions or variables declarations here
  
  crate(float x,float y, ofxBox2d &world/*,int crateSize*/); // constructor - used to initialize an object, if no properties are passed
  //               the program sets them to the default value

  
}; // dont't forget the semicolon!!

#endif
