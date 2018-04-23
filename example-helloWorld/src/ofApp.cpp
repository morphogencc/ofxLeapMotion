#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	mCamera.setOrientation(ofPoint(-20, 0, 0));
	mLeap = std::make_shared<ofxLeapMotion::LeapListener>();
	mLeap->open();
	mHand = ofxLeapMotion::ofxHand();
	mHand.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
	mHand.setMappingY(90, 490, 0, ofGetHeight() / 2);
	mHand.setMappingZ(-150, 150, -200, 200);
}

//--------------------------------------------------------------
void ofApp::update(){
	Leap::Frame currentFrame = mLeap->getFrame();
	mRightHand = ofxLeapMotion::getRightHand(currentFrame);
	if (mRightHand.isValid()) {
		std::printf("Found a valid right hand.\n");
		mHand.setHand(mRightHand);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30), OF_GRADIENT_BAR);
	ofSetColor(200);
	ofDrawBitmapString("ofxLeapMotion - Example App\nLeap Connected? " + ofToString(mLeap->isConnected()), 20, 20);

	mCamera.begin();

	ofPushMatrix();
	ofRotate(90, 0, 0, 1);
	ofSetColor(20);
	ofDrawGridPlane(800, 20, false);
	ofPopMatrix();

	if (mRightHand.isValid()) {
		mHand.draw();
	}

	mCamera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
