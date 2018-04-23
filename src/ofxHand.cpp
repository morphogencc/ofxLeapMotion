#include "ofxHand.h"

using namespace ofxLeapMotion;

ofxHand::ofxHand() {
	init();
}

ofxHand::ofxHand(Leap::Hand hand) {
	init();
	setHand(hand);
}

ofxHand::~ofxHand() {

}

void ofxHand::setHand(Leap::Hand hand) {
	mIsLeft = hand.isLeft();
	mHandPosition = convertToMappedPoint(hand.palmPosition());
	mHandNormal = convertToPoint(hand.palmNormal());
	mDirection = convertToPoint(hand.direction());
	mWristPosition = convertToMappedPoint(hand.wristPosition());
	mYaw = hand.direction().yaw();
	mRoll = hand.palmNormal().roll();
	mPitch = hand.direction().pitch();

	mFingers.clear();
	for (int j = 0; j < 5; j++) {
		const Leap::Finger &leapFinger = hand.fingers()[j];
		ofxLeapMotion::ofxFinger finger;

		finger.mPosition = convertToMappedPoint(leapFinger.tipPosition());
		finger.mVelocity = convertToMappedPoint(leapFinger.tipVelocity());

		finger.mJoints.push_back(convertToMappedPoint(leapFinger.jointPosition(leapFinger.JOINT_DIP)));
		finger.mJoints.push_back(convertToMappedPoint(leapFinger.jointPosition(leapFinger.JOINT_MCP)));
		finger.mJoints.push_back(convertToMappedPoint(leapFinger.jointPosition(leapFinger.JOINT_PIP)));
		finger.mJoints.push_back(convertToMappedPoint(leapFinger.jointPosition(leapFinger.JOINT_TIP)));

		mFingers.insert(std::pair<ofxLeapMotion::FINGER_TYPE, ofxFinger>(FINGER_TYPE(j), finger));
	}
}

void ofxHand::draw() {
	ofPushStyle();

	ofSetColor(190);
	ofSetLineWidth(2);

	ofEnableLighting();
	ofPushMatrix();
	ofTranslate(mHandPosition);

	//rotate the hand by the downwards normal
	//ofQuaternion q;
	//q.makeRotate(ofPoint(0, -1, 0), mHandNormal);
	//ofMatrix4x4 m;
	//q.get(m);
	//glMultMatrixf(m.getPtr());

	//scale it to make it not a box
	ofDrawBox(mHandPosition, 60);

	ofSetColor(0, 0, 0);
	for (int i = 0; i < 5; i++) {
		ofxLeapMotion::ofxFinger finger = mFingers[FINGER_TYPE(i)];
		for (int j = 0; j < 3; j++) {
			ofDrawArrow(finger.mJoints[j], finger.mJoints[j + 1], 10);
		}
	}

	/*
	ofDrawArrow(mHandPosition, mFingers[THUMB].mPosition, 10);
	ofDrawArrow(mHandPosition, mFingers[INDEX].mPosition, 10);
	ofDrawArrow(mHandPosition, mFingers[MIDDLE].mPosition, 10);
	ofDrawArrow(mHandPosition, mFingers[RING].mPosition, 10);
	ofDrawArrow(mHandPosition, mFingers[PINKY].mPosition, 10);

	ofSetColor(255, 255, 255);
	ofDrawArrow(mFingers[THUMB].mPosition + mFingers[THUMB].mVelocity / 20, mFingers[THUMB].mPosition + mFingers[THUMB].mVelocity / 10, 10);
	ofDrawArrow(mFingers[INDEX].mPosition + mFingers[INDEX].mVelocity / 20, mFingers[INDEX].mPosition + mFingers[INDEX].mVelocity / 10, 10);
	ofDrawArrow(mFingers[MIDDLE].mPosition + mFingers[MIDDLE].mVelocity / 20, mFingers[MIDDLE].mPosition + mFingers[MIDDLE].mVelocity / 10, 10);
	ofDrawArrow(mFingers[RING].mPosition + mFingers[RING].mVelocity / 20, mFingers[RING].mPosition + mFingers[RING].mVelocity / 10, 10);
	ofDrawArrow(mFingers[PINKY].mPosition + mFingers[PINKY].mVelocity / 20, mFingers[PINKY].mPosition + mFingers[PINKY].mVelocity / 10, 10);
	*/

	ofPopMatrix();
	ofDisableLighting();

	ofPopStyle();
}

void ofxHand::setMappingX(float minX, float maxX, float outputMinX, float outputMaxX) {
	mOffsetIn.x = minX;
	mOffsetOut.x = outputMinX;
	mScale.x = (outputMaxX - outputMinX) / (maxX - minX);
}

void ofxHand::setMappingY(float minY, float maxY, float outputMinY, float outputMaxY) {
	mOffsetIn.y = minY;
	mOffsetOut.y = outputMinY;
	mScale.y = (outputMaxY - outputMinY) / (maxY - minY);
}

void ofxHand::setMappingZ(float minZ, float maxZ, float outputMinZ, float outputMaxZ) {
	mOffsetIn.z = minZ;
	mOffsetOut.z = outputMinZ;
	mScale.z = (outputMaxZ - outputMinZ) / (maxZ - minZ);
}

void ofxHand::init() {
	mIsLeft = false;
	mHandPosition = ofPoint();
	mHandNormal = ofPoint();
	mDirection = ofPoint();
	mWristPosition = ofPoint();
	mYaw = 0;
	mRoll = 0;
	mPitch = 0;
	mOffsetIn = ofPoint();
	mOffsetOut = ofPoint();
	mScale = ofPoint();
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
