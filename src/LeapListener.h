#include <memory>
#include <string>
#include <mutex>
#include <chrono>
#include "Leap.h"

namespace ofxLeapMotion {
  class LeapListener : public Leap::Listener {
    public:
      LeapListener();
      ~LeapListener();
      void open();
      void close();
	  const Leap::Frame getFrame();
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
	  Leap::Frame mFrame;
  };
}
