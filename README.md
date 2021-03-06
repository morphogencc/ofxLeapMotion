# ofxLeapMotion
Wrapper for the Leap Motion v2.3.1 SDK.

## Requirements
* [Leap Motion SDK v2.3.1](https://developer.leapmotion.com/sdk/v2/)
* jsoncpp -- I only use this for loading config files, and use the C++ api for jsoncpp.  For ease of use, just grab  [ofxJson](https://github.com/jeffcrouse/ofxJSON).

If your computer is having trouble detecting the Leap Motion after you've installed the SDK, you may need to install the drivers located at `C:\Program Files (x86)\Leap Motion\Core Services\Drivers`.

## Compatibility Issues
openFrameworks v0.9.7 has several preprocessor directives that conflict with the Leap Motion SDK (mostly constants like `PI` and `RAD_TO_DEG`).  As of 2018 April 21, this library is using a slightly modified version of the Leap Motion SDK with the constants redefined as with a `LEAP_` prefix.  This doesn't seem to have any impact on usage, but if you try to upgrade to a newer version of the SDK you'll find you need to do resolve this.

## Contributions
Huge thanks to ofTheo and genekogan for their previous implementations -- their design choices impacted how I put this together quite a bit.
