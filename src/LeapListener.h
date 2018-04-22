#include <memory>
#include <string>
#include <mutex>
#include <chrono>
#include "Leap.h"

namespace ofxLeapMotion {
  const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
  const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
  const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

  class LeapListener : public Leap::Listener {
    public:
      LeapListener();
      ~LeapListener();
      void open();
      void close();
      virtual void onConnect(const Leap::Controller &controller);
      virtual void onDeviceChange(const Leap::Controller &controller);
      virtual void onDeviceFailure(const Leap::Controller &controller);
      virtual void onDisconnect(const Leap::Controller &controller);
      virtual void onExit(const Leap::Controller &controller);
      virtual void onFocusGained(const Leap::Controller &controller);
      virtual void onFocusLost(const const Leap::Controller &controller);
      virtual void onFrame(const Leap::Controller &controller);
      virtual void onImages(const Leap::Controller &controller);
      virtual void onInit(const Leap::Controller &controller);
      virtual void onLogMessage(const Leap::Controller &controller);
      virtual void onServiceChange(const Leap::Controller &controller);
      virtual void onServiceConnect(const Leap::Controller &controller);
      virtual void onServiceDisconnect(const Leap::Controller &controller);
    protected:
      std::shared_ptr<Leap::Controller> mController;
	  std::mutex mFrameMutex;
	  Leap::Hand mRightHand;
	  Leap::FingerList mRightFingers;
	  Leap::FingerList mRingFinger;
	  std::chrono::system_clock::time_point mStartTime;
  };
}
