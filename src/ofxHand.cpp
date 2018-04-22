#include "ofxHand.h"

using namespace ofxLeapMotion;

ofxHand::ofxHand() {

}

ofxHand::ofxHand(Leap::Hand hand) {
  mIsLeft = hand.isLeft();
  mHandPosition = convertToMappedPoint(hand.palmPosition());
  mHandNormal = convertToPoint(hand.palmNormal());
  mDirection = convertToPoint(hand.direction());
  mWristPosition = convertToMappedPoint(hand.wristPosition());
  mYaw = hand.direction().yaw();
  mRoll = hand.palmNormal().roll();
  mPitch = hand.direction().pitch();
  mOffsetIn = ofPoint(0,0,0);
  mOffsetOut = ofPoint(0,0,0);
  mScale = ofPoint(1,1,1);
}

ofxHand::~ofxHand() {

}

void ofxHand::draw() {
  ofPushStyle();

  ofSetColor(190);
  ofSetLineWidth(2);

  ofEnableLighting();
  ofPushMatrix();
  ofTranslate(mHandPosition);

  //rotate the hand by the downwards normal
  ofQuaternion q;
  q.makeRotate(ofPoint(0, -1, 0), mHandNormal);
  ofMatrix4x4 m;
  q.get(m);
  glMultMatrixf(m.getPtr());

  //scale it to make it not a box
  ofScale(1, 0.35, 1.0);
  #if (OF_VERSION_MAJOR == 0) && (OF_VERSION_MINOR < 8)
  ofBox(0, 0, 0, 60);
  #else
  ofDrawBox(0, 0, 0, 60);
  #endif
  ofPopMatrix();

  ofDrawArrow(mHandPosition, mFingers[THUMB].mPosition, 10);
  ofDrawArrow(mHandPosition, mFingers[INDEX].mPosition, 10);
  ofDrawArrow(mHandPosition, mFingers[MIDDLE].mPosition, 10);
  ofDrawArrow(mHandPosition, mFingers[RING].mPosition, 10);
  ofDrawArrow(mHandPosition, mFingers[PINKY].mPosition, 10);

  ofSetColor(220, 220, 0);
  ofDrawArrow(mFingers[THUMB].mPosition + mFingers[THUMB].mVelocity/20, mFingers[THUMB].mPosition + mFingers[THUMB].mVelocity/10, 10);
  ofDrawArrow(mFingers[INDEX].mPosition + mFingers[INDEX].mVelocity/20, mFingers[INDEX].mPosition + mFingers[INDEX].mVelocity/10, 10);
  ofDrawArrow(mFingers[MIDDLE].mPosition + mFingers[MIDDLE].mVelocity/20, mFingers[MIDDLE].mPosition + mFingers[MIDDLE].mVelocity/10, 10);
  ofDrawArrow(mFingers[RING].mPosition + mFingers[RING].mVelocity/20, mFingers[RING].mPosition + mFingers[RING].mVelocity/10, 10);
  ofDrawArrow(mFingers[PINKY].mPosition + mFingers[PINKY].mVelocity/20, mFingers[PINKY].mPosition + mFingers[PINKY].mVelocity/10, 10);

  ofDisableLighting();

  ofPopStyle();
}

void ofxHand::setMappingX(float minX, float maxX, float outputMinX, float outputMaxX){
  mOffsetIn.x = minX;
  mOffsetOut.x = outputMinX;
  mScale.x = (outputMaxX - outputMinX) / (maxX - minX);
}

void ofxHand::setMappingY(float minY, float maxY, float outputMinY, float outputMaxY){
  mOffsetIn.y	= minY;
  mOffsetOut.y = outputMinY;
  mScale.y = (outputMaxY - outputMinY) / (maxY - minY);
}

void ofxHand::setMappingZ(float minZ, float maxZ, float outputMinZ, float outputMaxZ){
  mOffsetIn.z	= minZ;
  mOffsetOut.z = outputMinZ;
  mScale.z = (outputMaxZ - outputMinZ) / (maxZ - minZ);
}

ofPoint ofxHand::convertToPoint(Leap::Vector vector) {
  return ofPoint(vector.x, vector.y, vector.z);
}

ofPoint ofxHand::convertToMappedPoint(Leap::Vector vector) {
  ofPoint point = convertToPoint(vector);
  point.x = mOffsetOut.x + (point.x - mOffsetIn.x) * mScale.x;
  point.y = mOffsetOut.y + (point.y - mOffsetIn.y) * mScale.y;
  point.z = mOffsetOut.z + (point.z - mOffsetIn.z) * mScale.z;

  return point;
}
