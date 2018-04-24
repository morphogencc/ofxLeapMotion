#pragma once

#include "Leap.h"

namespace ofxLeapMotion {
	static const float LEAP_PIX_PER_MM = 11.811; // 300 pixels per inch in pixels per mm

	static const float LEAP_MIN_X_MM = -117.5;
	static const float LEAP_MAX_X_MM = 117.5;
	static const float LEAP_MIN_Y_MM = 82.5;
	static const float LEAP_MAX_Y_MM = 317.5;
	static const float LEAP_MIN_Z_MM = -73.5;
	static const float LEAP_MAX_Z_MM = 73.5;

	static const std::string FingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
	static const std::string BoneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };
	static const std::string StateNames[] = { "STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END" };

	const float toPixels(float millimeters);

	const float toMillimeters(float pixels);

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
