#include <fstream>
#include "LeapListener.h"

using namespace ofxLeapMotion;

LeapListener::LeapListener() {
	mController = std::make_shared<Leap::Controller>();
	mIsFrameNew = false;
	mIsConnected = false;
	mLeapOrigin = Leap::Vector(0, 0, 0);
	mLeapRotation = Leap::Vector(0, 0, 0);
}

LeapListener::~LeapListener() {
}

void LeapListener::open() {
	mController->addListener(*this);
}

void LeapListener::close() {
	mController->removeListener(*this);
}

const Leap::Frame LeapListener::getFrame() {
	std::lock_guard<std::mutex> lockGuard(mFrameMutex);
	mIsFrameNew = false;
	return mFrame;
}

const bool LeapListener::isConnected() {
	return mIsConnected;
}

void LeapListener::loadConfiguration(std::string filename) {
	Json::Value fileRoot;
	Json::Reader reader;
	std::ifstream jsonFile(filename.c_str());

	if (!reader.parse(jsonFile, fileRoot, false)) {
		std::printf("ofxLeapMotion::LeapListener -- failed to load configuration file at %s!\n", filename.c_str());
		std::printf("ofxLeapMotion::LeapListener -- Reason of Failure: %s\n", reader.getFormattedErrorMessages().c_str());
		return;
	}
	Json::Value position = fileRoot["position"];
	mLeapOrigin = Leap::Vector(position[0].asFloat(), position[1].asFloat(), position[2].asFloat());
	Json::Value rotation = fileRoot["rotation"];
	mLeapRotation = Leap::Vector(rotation[0].asFloat(), rotation[1].asFloat(), rotation[2].asFloat());
}

const Leap::Vector LeapListener::getLeapOrigin() {
	return mLeapOrigin;
}

const Leap::Vector LeapListener::getLeapRotation() {
	return mLeapRotation;
}

void LeapListener::onConnect(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onConnect -- connected!\n");
	mIsConnected = true;
}

void LeapListener::onDeviceChange(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onDeviceChange\n");
	const Leap::DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::printf("id: %s\n", devices[i].toString().c_str());
		std::printf("isStreaming: %s", (devices[i].isStreaming() ? "true" : "false"));
	}
}

void LeapListener::onDeviceFailure(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onDeviceFailure\n");
}

void LeapListener::onDisconnect(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onDisconnect -- Disconnected.\n");
}

void LeapListener::onExit(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onExit -- exited.\n");
}

void LeapListener::onFocusGained(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onFocusGained\n");
}

void LeapListener::onFocusLost(const const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onFocusLost\n");
}

void LeapListener::onFrame(const Leap::Controller &controller) {
	mFrameMutex.lock();
	mFrame = mController->frame();
	mIsFrameNew = true;
	mFrameMutex.unlock();
}

void LeapListener::onImages(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onImages -- new images available.\n");
}

void LeapListener::onInit(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onInit -- Controller initialized.\n");
}

void LeapListener::onLogMessage(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onLogMessage\n");
}

void LeapListener::onServiceChange(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onServiceChange\n");
}

void LeapListener::onServiceConnect(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onServiceConnect\n");
}

void LeapListener::onServiceDisconnect(const Leap::Controller &controller) {
	std::printf("ofxLeapMotion::LeapListener::onServiceDisconnect\n");
}
