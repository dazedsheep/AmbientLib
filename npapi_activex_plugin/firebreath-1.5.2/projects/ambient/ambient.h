/**********************************************************\

  Auto-generated ambient.h

  This file contains the auto-generated main plugin object
  implementation for the ambient project

\**********************************************************/
#ifndef H_ambientPLUGIN
#define H_ambientPLUGIN

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include "PluginCore.h"


FB_FORWARD_PTR(ambient)
class ambient : public FB::PluginCore
{
private:
	HANDLE calcMutex;
	Ambient *ambientLib;
	int framesToSkip;
	int actualFrameCount;

	HWND flashPlugin;
	RECT winrect;

	unsigned int parentWidth;
	unsigned int parentHeight;

	int errorMessage;

	HDC screenHDC;				// handle for the screen
	int screenX,screenY;		// screen metrics
	unsigned int width,height;
	HDC hdcMemory;				// memory handle
	HBITMAP hbmMemory;			// bitmap handle
	HBITMAP hbmOld;
	BITMAPINFO bInfo;

	//EPOC SECTION
#ifdef USE_EPOC
	bool epocReady;
	EmoEngineEventHandle epocEvent;
	EmoStateHandle epocState;
	DataHandle hData;
	unsigned int epocUserId;
	float epocBufferInSecs;

#endif


public:
    static void StaticInitialize();
    static void StaticDeinitialize();

public:
    ambient();
    virtual ~ambient();

public:
    void onPluginReady();
    void shutdown();
    virtual FB::JSAPIPtr createJSAPI();
    // If you want your plugin to always be windowless, set this to true
    // If you want your plugin to be optionally windowless based on the
    // value of the "windowless" param tag, remove this method or return
    // FB::PluginCore::isWindowless()
    virtual bool isWindowless() { return false; }


    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
    virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
    virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/


	int getErrorMessage();

	int setCalculationRate(int pixelJump, int rowJump);
	int threadedCalculation(int width, int height, std::string &d);
	int calcFrame();
#ifdef USE_EPOC
	int initialize(int framesToSkip, unsigned int width, unsigned int height, float EPOC_BUFFER_SIZE_IN_SECS);
	std::string queryEPOC();	// will return a xml tag with the EEG data ...
#else
	int initialize(int framesToSkip,unsigned int width, unsigned int height);
#endif
	unsigned long t();
	unsigned int threadedCalculationFullscreen();
	void disableAmbient();
	void loadSEM(std::string url, std::string file);
	void playEffectAtTimeAbs(double time);
	void playEffectAtTimeRel(double time);
	unsigned int getWidth(unsigned int width, unsigned int height);
	unsigned int getHeight();
	unsigned int grabFrame(unsigned int webBrowser, unsigned int scwidth, unsigned scheight, unsigned int widht, unsigned int height);




};


#endif

