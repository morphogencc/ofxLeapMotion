#pragma once
#include "Leap.h"

namespace ofxLeapMotion {
	static const std::string sFingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
	static const std::string sBoneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };
	static const std::string sStateNames[] = { "STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END" };

	const std::string getFingerName(Leap::Finger::Type fingerType) {
		return sFingerNames[fingerType];
	}

	const std::string getBoneName(Leap::Bone::Type boneType) {
		return sBoneNames[boneType];
	}

	const Leap::Hand getRightHand(const Leap::Frame frame) {
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

	const Leap::Hand getLeftHand(const Leap::Frame frame) {
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

	const Leap::Finger getFinger(const Leap::Hand hand, Leap::Finger::Type type) {
		/*
		You'll need to check if the finger is valid (using finger.isValid()) before using it; it could be a null finger.
		*/
		Leap::Finger finger = Leap::Finger();
		Leap::FingerList fingers = hand.fingers();
		for (Leap::FingerList::const_iterator iter = fingers.begin(); iter != fingers.end(); ++iter) {
			Leap::Finger f = *iter;
			if (f.type == type) {
				finger = f;
			}
		}
	}

	const Leap::Bone getBone(const Leap::Finger finger, Leap::Bone::Type type) {
		/*
		You'll need to check if the bone is valid (using bone.isValid()) before using it; it could be a null bone.
		*/
		Leap::Bone bone = Leap::Bone();
		bone = finger.bone(type);
		return bone;
	}

}