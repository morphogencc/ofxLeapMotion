#pragma once

#include "Leap.h"
#include "LeapUtils.h"

const std::string sFingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string sBoneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };
const std::string sStateNames[] = { "STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END" };

const std::string ofxLeapMotion::getFingerName(Leap::Finger::Type fingerType) {
	return sFingerNames[fingerType];
}

const std::string ofxLeapMotion::getBoneName(Leap::Bone::Type boneType) {
	return sBoneNames[boneType];
}

const Leap::Hand ofxLeapMotion::getRightHand(const Leap::Frame frame) {
	/*
	You'll need to check if this hand is valid (using hand.isValid()) before using it; it could be a null object.
	*/
	Leap::Hand rightHand = Leap::Hand();
	Leap::HandList handList = frame.hands();
	for (Leap::HandList::const_iterator iter = handList.begin(); iter != handList.end(); ++iter) {
		const Leap::Hand hand = *iter;
		if (hand.isRight()) {
			rightHand = hand;
		}
	}
	return rightHand;
}

const Leap::Hand ofxLeapMotion::getLeftHand(const Leap::Frame frame) {
	/*
	You'll need to check if this hand is valid (using hand.isValid()) before using it; it could be a null object.
	*/
	Leap::Hand leftHand = Leap::Hand();
	const Leap::HandList handList = frame.hands();
	for (Leap::HandList::const_iterator iter = handList.begin(); iter != handList.end(); ++iter) {
		const Leap::Hand hand = *iter;
		if (hand.isLeft()) {
			leftHand = hand;
		}
	}
	return leftHand;
}

const Leap::Finger ofxLeapMotion::getFinger(const Leap::Hand hand, Leap::Finger::Type type) {
	/*
	You'll need to check if the finger is valid (using finger.isValid()) before using it; it could be a null finger.
	*/
	Leap::Finger finger = Leap::Finger();
	Leap::FingerList fingers = hand.fingers();
	for (Leap::FingerList::const_iterator iter = fingers.begin(); iter != fingers.end(); ++iter) {
		Leap::Finger f = *iter;
		if (f.type() == type) {
			finger = f;
		}
	}
	return finger;
}

const Leap::Bone ofxLeapMotion::getBone(const Leap::Finger finger, Leap::Bone::Type type) {
	/*
	You'll need to check if the bone is valid (using bone.isValid()) before using it; it could be a null bone.
	*/
	Leap::Bone bone = Leap::Bone();
	bone = finger.bone(type);
	return bone;
}

/*
const Leap::Vector ofxLeapMotion::LeapToWorld(Leap::Vector leapPosition, Leap::Matrix transformationMatrix) {
}

const Leap::Vector ofxLeapMotion::WorldToLeap(Leap::Vector worldPosition, Leap::Matrix transformationMatrix) {
}
*/