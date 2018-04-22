#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ofxLeapMotion.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class cinderExampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	std::shared_ptr<ofxLeapMotion::LeapListener> mLeap;
};

void cinderExampleApp::setup() {
	mLeap = std::make_shared<ofxLeapMotion::LeapListener>();
}

void cinderExampleApp::mouseDown( MouseEvent event )
{
}

void cinderExampleApp::update()
{
}

void cinderExampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( cinderExampleApp, RendererGl )
