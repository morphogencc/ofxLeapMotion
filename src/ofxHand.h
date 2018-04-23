#pragma once

#include <map>
#include "Leap.h"
#include "ofMain.h"

/*
* Uses only openFrameworks classes to represent a hand in a way that can be easily drawn.
* Almost entirely lifted from Gene Kogan's ofxLeapMotion2
* https://github.com/genekogan/ofxLeapMotion2
*
* The goal of this class is to allow users to extract information from the hand without using the Leap Motion SDK
*
*
*/

namespace ofxLeapMotion {
	enum FINGER_TYPE {
		THUMB,
		INDEX,
		MIDDLE,
		RING,
		PINKY
	};

	struct ofxFinger {
		ofPoint mPosition;
		ofPoint mVelocity;
		std::vector<ofPoint> mJoints[4];
	};

	class ofxHand {
	public:
		ofxHand();
		ofxHand(Leap::Hand hand);
		~ofxHand();
		void setHand(Leap::Hand hand);
		void draw();
		void setMappingX(float minX, float maxX, float outputMinX, float outputMaxX);
		void setMappingY(float minY, float maxY, float outputMinY, float outputMaxY);
		void setMappingZ(float minZ, float maxZ, float outputMinZ, float outputMaxZ);
	protected:
		void init();
		ofPoint convertToPoint(Leap::Vector vector);
		ofPoint convertToMappedPoint(Leap::Vector vector);
		std::map<ofxLeapMotion::FINGER_TYPE, ofxFinger> mFingers;
		bool mIsLeft;
		ofPoint mHandPosition;
		ofPoint mHandNormal;
		ofPoint mDirection;
		ofPoint mWristPosition;
		ofPoint mOffsetIn;
		ofPoint mOffsetOut;
		ofPoint mScale;
		float mYaw;
		float mRoll;
		float mPitch;
	};
}
