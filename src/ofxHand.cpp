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

	ofEnableLighting();

	ofPushMatrix();

	ofTranslate(mHandPosition);

	ofSetColor(190);
	ofSetLineWidth(2);
	ofDrawBox(mHandPosition, ofxLeapMotion::toPixels(25), ofxLeapMotion::toPixels(5), ofxLeapMotion::toPixels(25));

	ofSetColor(0, 0, 0);
	for (int i = 0; i < 5; i++) {
		ofxLeapMotion::ofxFinger finger = mFingers[FINGER_TYPE(i)];
		for (int j = 0; j < 3; j++) {
			ofDrawArrow(finger.mJoints[j], finger.mJoints[j + 1], 10);
		}
	}

	ofPopMatrix();

	ofDisableLighting();

	ofPopStyle();
}

const ofPoint ofxHand::getPosition() {
	return mHandPosition;
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
	point.x = ofxLeapMotion::toPixels(point.x);
	point.y = ofxLeapMotion::toPixels(point.y);
	point.z = ofxLeapMotion::toPixels(point.z);
	return point;
}
