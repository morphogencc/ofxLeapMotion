#pragma once

#include "Leap.h"

namespace ofxLeapMotion {

	const std::string getFingerName(Leap::Finger::Type fingerType);

	const std::string getBoneName(Leap::Bone::Type boneType);

	const Leap::Hand getRightHand(const Leap::Frame frame);

	const Leap::Hand getLeftHand(const Leap::Frame frame);
	
	const Leap::Finger getFinger(const Leap::Hand hand, Leap::Finger::Type type);
	
	const Leap::Bone getBone(const Leap::Finger finger, Leap::Bone::Type type);
	/*
	const Leap::Vector LeapToWorld(Leap::Vector leapPosition, Leap::Matrix transformationMatrix);

	const Leap::Vector WorldToLeap(Leap::Vector worldPosition, Leap::Matrix transformationMatrix);
	*/
}
