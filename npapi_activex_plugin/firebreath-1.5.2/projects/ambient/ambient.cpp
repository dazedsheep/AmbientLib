/**********************************************************\

  Auto-generated ambient.cpp

  This file contains the auto-generated main plugin object
  implementation for the ambient project

\**********************************************************/
#include "../../../../AmbientLib/AmbientLib.h"
#include "PluginWindowWin.h"
#include "PluginWindowlessWin.h"

#ifdef USE_EPOC
#include "EmoStateDLL.h"
#include "edk.h"
#include "edkErrorCode.h"
#endif

#include <stdlib.h>
#include <direct.h>
#include <Windows.h>
#include <iostream>
#include <sstream>

#include "ambientAPI.h"

#include "ambient.h"

#ifdef USE_EPOC
EE_DataChannel_t targetChannelList[] = {
		ED_AF3, ED_F7, ED_F3, ED_FC5, ED_T7, 
		ED_P7, ED_O1, ED_O2, ED_P8, ED_T8, 
		ED_FC6, ED_F4, ED_F8, ED_AF4, ED_GYROX, ED_GYROY, ED_TIMESTAMP
};


#define stringify( name ) # name
const char* EEGChannelNames[] = 
  {
  stringify( COUNTER ),
  stringify( INTERPOLATED  ),
  stringify( RAW_CQ ),
  stringify( af3 ),
  stringify( f7 ),
  stringify( f3 ),
  stringify( fc5 ),
  stringify( t7 ),
  stringify( p7 ),
  stringify( o1 ),
  stringify( o2 ),
  stringify( p8 ),
  stringify( t8 ),
  stringify( fc6 ),
  stringify( f4 ),
  stringify( f8 ),
  stringify( af4 ),
  stringify( x ),
  stringify( y ),
  stringify( TIMESTAMP ),
  stringify( ES_TIMESTAMP ),
  stringify( ED_FUNC_ID ),
  stringify( FUNC_VALUE ),
  stringify( MARKER ),
  stringify( SYNC_SIGNAL )
  };

#endif

using namespace std;
///////////////////////////////////////////////////////////////////////////////
/// @fn ambient::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void ambient::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
	
}

///////////////////////////////////////////////////////////////////////////////
/// @fn ambient::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void ambient::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded

}

///////////////////////////////////////////////////////////////////////////////
/// @brief  ambient constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
ambient::ambient()
{
	//	::MessageBoxA(NULL, ("constructor"),("ambient plugin"), MB_OK);
	calcMutex = CreateMutex(NULL,FALSE,NULL);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  ambient destructor.
///////////////////////////////////////////////////////////////////////////////
ambient::~ambient()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
	//::MessageBoxA(NULL, ("deconstructor"),("ambient plugin"), MB_OK);

    releaseRootJSAPI();
    m_host->freeRetainedObjects();
	
}

void ambient::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
	ambientLib = NULL;
}

void ambient::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
	//::MessageBoxA(NULL, "shutting down ambient plugin","ambient plugin", MB_OK);
#ifdef USE_EPOC
	EE_EngineDisconnect();

	if(epocState != NULL) EE_EmoStateFree(epocState);

	if(epocEvent != NULL) EE_EmoEngineEventFree(epocEvent);
#endif
	if(ambientLib!=NULL) delete ambientLib;
	
	CloseHandle(this->calcMutex);


}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<ambient> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr ambient::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<ambientAPI>(FB::ptr_cast<ambient>(shared_from_this()), m_host);
}

bool ambient::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool ambient::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool ambient::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
bool ambient::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return false;
}

bool ambient::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}


unsigned int ambient::grabFrame(unsigned int webBrowser, unsigned int scwidth, unsigned int scheight, unsigned int width, unsigned int height)
{

	FB::PluginWindow *plgwin = this->GetWindow();
	FB::PluginWindowWin *plgwindows = (FB::PluginWindowWin *)plgwin;
	HWND parent=NULL,child=NULL;
	WINDOWINFO inf;
	inf.cbSize = sizeof(WINDOWINFO);
	flashPlugin = NULL;
	if(webBrowser != AUTO_FETCH)
	{
		if(webBrowser == MOZILLA_FIREFOX)
		{
			parent = plgwindows->getBrowserHWND();	// <-- GeckoPluginWindow
			parent = ::GetParent(parent);				// <--- MozillaWindowClass (intermediate window)
			parent = ::GetParent(parent);				// <--- MozillaWindowClass (main window)

			child = ::GetWindow(parent,GW_CHILD);		// <--- The first MozillaWindowClass
			GetWindowInfo(child, &inf);
			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				GetWindowInfo(child,&inf);
			};
			if(child == NULL) return 3;				// no such window
			child = ::GetWindow(child,GW_CHILD);

			flashPlugin = child;

		}else if(webBrowser == OPERA)
		{

			parent = plgwindows->getBrowserHWND();	//<--- OperaWindowClass
			//parent = GetParent(parent);				
	
			child = ::GetWindow(parent,GW_CHILD);		// <--- The first aPluginWindowClass
			GetWindowInfo(child, &inf);
			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				::GetWindowInfo(child,&inf);
			};
			if(child == NULL) return 3;				// no such window
		

			flashPlugin = child;


		}else if(webBrowser == MICROSOFT_IE)
		{
			parent = ::GetParent(plgwindows->getHWND());
			
			child = ::GetWindow(parent,GW_CHILD);
			::GetWindowInfo(child,&inf);

			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				::GetWindowInfo(child,&inf);
			};
			if(child == NULL) return 3;				// no such window
			flashPlugin = child;

		}else if(webBrowser == GOOGLE_CHROME)
		{
			parent = plgwindows->getBrowserHWND();	// <-- NativeWindowClass
			parent = ::GetParent(parent);				// <-- WrapperNativeWindowClass
			parent = ::GetParent(parent);				// <-- Chrome_RenderWidgetHost

			child = ::GetWindow(parent,GW_CHILD);		// <-- The first NativeWindowClass(Plugin) of this page
			GetWindowInfo(child,&inf);
			// try to find the window with the given resolution
			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				GetWindowInfo(child,&inf);
			};
			if(child == NULL) return 3;				// no such window

			//child = GetWindow(child,GW_CHILD);

			flashPlugin = child;
			// we have our HWND
				
		}else if(webBrowser == SAFARI)
		{
			unsigned int winOrder;
			parent = plgwindows->getBrowserHWND();
			// because of the content script the plugin is always the last window so just step backwards and grep the flash plugin

			// TODO: if we are not the last one
			if(::GetNextWindow(parent,GW_HWNDPREV) == NULL) winOrder = GW_HWNDNEXT;
			else
			{
				// step back
				while (::GetNextWindow(parent,GW_HWNDPREV) != NULL) parent = ::GetNextWindow(parent,GW_HWNDPREV);
				winOrder = GW_HWNDNEXT;
			}

			while(parent != NULL)
			{
				// we have to get the child of every window
				child = ::GetWindow(parent,GW_CHILD);
				if(child != NULL) {
					GetWindowInfo(child,&inf);
					if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				}
				parent = ::GetNextWindow(parent,winOrder);
			}
			if(parent == NULL || child == NULL) return 3;

			flashPlugin = child;

		}else{

			return 2; //not supported
		}
	}else{
		// try to fetch the window automatically ... test each browser strategy

		// if the browser hwnd is NULL, then we are in the internet explorer ...
		if(plgwindows->getBrowserHWND() == NULL)
		{
			parent = GetParent(plgwindows->getHWND());
			
			child = ::GetWindow(parent,GW_CHILD);
			GetWindowInfo(child,&inf);

			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				GetWindowInfo(child,&inf);
			};
			if(child != NULL) flashPlugin = child;
		}

		if(child == NULL)
		{
			// mozilla
			parent = plgwindows->getBrowserHWND();	// <-- GeckoPluginWindow
			parent = GetParent(parent);				// <--- MozillaWindowClass (intermediate window)
			parent = GetParent(parent);				// <--- MozillaWindowClass (main window)

			child = ::GetWindow(parent,GW_CHILD);		// <--- The first MozillaWindowClass
			GetWindowInfo(child, &inf);
			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				::GetWindowInfo(child,&inf);
			};
			if(child != NULL)
			{ 			
				child = ::GetWindow(child,GW_CHILD);

				flashPlugin = child;
			}
		}
		if(child == NULL)						// no such window, next strategy
		{
			parent = plgwindows->getBrowserHWND();	//<--- OperaWindowClass
			//parent = GetParent(parent);				
	
			child = ::GetWindow(parent,GW_CHILD);		// <--- The first aPluginWindowClass
			GetWindowInfo(child, &inf);
			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				GetWindowInfo(child,&inf);
			};
			if(child != NULL) flashPlugin = child;				
		}
		if(child == NULL)						// and again
		{
			parent = plgwindows->getBrowserHWND();	// <-- NativeWindowClass
			parent = GetParent(parent);				// <-- WrapperNativeWindowClass
			parent = GetParent(parent);				// <-- Chrome_RenderWidgetHost

			child = ::GetWindow(parent,GW_CHILD);		// <-- The first NativeWindowClass(Plugin) of this page
			GetWindowInfo(child,&inf);
			// try to find the window with the given resolution
			while(child != NULL)
			{
				if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				child = ::GetNextWindow(child,GW_HWNDNEXT);
				GetWindowInfo(child,&inf);
			};
			if(child != NULL) flashPlugin = child;				// no such window

			//child = GetWindow(child,GW_CHILD);

			
			// we have our HWND
		}
		if(child == NULL)
		{
			unsigned int winOrder;
			parent = plgwindows->getBrowserHWND();
			// because of the content script the plugin is always the last window so just step backwards and grep the flash plugin

			// TODO: if we are not the last one
			if(::GetNextWindow(parent,GW_HWNDPREV) == NULL) winOrder = GW_HWNDNEXT;
			else
			{
				// setp back
				while (::GetNextWindow(parent,GW_HWNDPREV) != NULL) parent = ::GetNextWindow(parent,GW_HWNDPREV);
				winOrder = GW_HWNDNEXT;
			}


			while(parent != NULL)
			{
				// we have to get the child of every window
				child = ::GetWindow(parent,GW_CHILD);
				if(child != NULL) {
					GetWindowInfo(child,&inf);
					if((inf.rcClient.right - inf.rcClient.left) == width && (inf.rcClient.bottom - inf.rcClient.top)==height) break;
				}
				parent = ::GetNextWindow(parent,winOrder);
			}
			if(parent != NULL && child != NULL)	flashPlugin = child;

			

		}
		if(flashPlugin == NULL) return 3;		//hmm...

	}
	
	GetWindowRect(flashPlugin,&winrect);

	// we may have the window handle but, since we are calling this on a timer it may happen that we enter this section twice
	// prevent this behavior with a mutex
	if(WaitForSingleObject(this->calcMutex,1) == WAIT_TIMEOUT) return 4;

	// grab a frame from the flash plugin embedded in the active page
	HDC flashHDC = GetWindowDC(flashPlugin);
	HDC Memory = CreateCompatibleDC(flashHDC);
	HBITMAP bmMemory = CreateCompatibleBitmap(flashHDC,winrect.right-winrect.left,winrect.bottom-winrect.top);
	HBITMAP Old = (HBITMAP) SelectObject(Memory, bmMemory);
	
	//BitBlt(Memory,0,30,winrect.right-winrect.left,winrect.bottom-winrect.top,flashHDC,0,0,SRCCOPY);
	// mirror the image vertical and scale it
	StretchBlt(Memory,0,0,scwidth,scheight,flashHDC,0,0,winrect.right-winrect.left,winrect.bottom-winrect.top,SRCCOPY);
	

	BITMAPINFO Info;
	ZeroMemory(&Info, sizeof(BITMAPINFO));
	Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Info.bmiHeader.biWidth = scwidth;
	Info.bmiHeader.biHeight = -scheight;
	Info.bmiHeader.biBitCount = 32;
	Info.bmiHeader.biCompression = BI_RGB;
	Info.bmiHeader.biPlanes = 1;

	
	GetDIBits(Memory,bmMemory,0,scheight,NULL,&Info,DIB_RGB_COLORS);
		// now copy the image to our buffer

		// NOTE: it's a BGR frame ...
	if(Info.bmiHeader.biSizeImage == 0) 
	{
		SelectObject(Memory, Old);
		ReleaseDC(flashPlugin,Memory);
		ReleaseDC(flashPlugin,flashHDC);
		DeleteObject(bmMemory);
		DeleteDC(Memory);
		ReleaseMutex(this->calcMutex);
		return 4;
	}
	unsigned char *data = (unsigned char *)malloc(Info.bmiHeader.biSizeImage);
	ZeroMemory(data,Info.bmiHeader.biSizeImage);
	GetDIBits(Memory,bmMemory,0,scheight,data,&Info,DIB_RGB_COLORS);
	SelectObject(Memory, Old);
	ReleaseDC(flashPlugin,Memory);
	ReleaseDC(flashPlugin,flashHDC);
	DeleteDC(Memory);
	DeleteObject(bmMemory);

	ambientLib->lightFromPicture(data,IMAGE_FORMAT_BGRA);
	
	
	free(data);

	ReleaseMutex(this->calcMutex);

	return 0;
}


unsigned int ambient::getHeight()
{
	FB::PluginWindow *plgwin = this->GetWindow();
	HWND parent;
	RECT winrect;
	WINDOWINFO inf;
	inf.cbSize = sizeof(WINDOWINFO);
	if(this->isWindowless())
	{
		FB::PluginWindowlessWin *plgwindows = (FB::PluginWindowlessWin *) plgwin;
		parent = plgwindows->getHWND();
		// again down one step
		parent = GetParent(parent);
			GetWindowInfo(parent,&inf);
		GetWindowRect(parent,&winrect);
		parentWidth = winrect.right;
		parentHeight = winrect.bottom;


	}else{

		FB::PluginWindowWin *plgwindows = (FB::PluginWindowWin *)plgwin;
		parent = plgwindows->getBrowserHWND();
		GetWindowInfo(parent,&inf);
		GetWindowRect(parent,&winrect);
		parentWidth = winrect.right;
		parentHeight = winrect.bottom;

	}
	return parentHeight;
}

int ambient::getErrorMessage()
{

	return errorMessage;
}

void ambient::loadSEM(std::string url, std::string file)
{
//	::MessageBoxA(NULL, ("loading SEM"),("ambient plugin"), MB_OK);
	ambientLib->loadSEMHTTP(url.c_str(),file.c_str(), false);		// use directory lookup
//	::MessageBoxA(NULL, ("done loading SEM"),("ambient plugin"), MB_OK);
	
}

void ambient::playEffectAtTimeRel(double time)
{

	ambientLib->playEffectAtTimeRel(time);
}

void ambient::playEffectAtTimeAbs(double time)
{
	ambientLib->playEffectAtTimeAbs(time);
}

#ifdef USE_EPOC

std::string ambient::queryEPOC()
{

	unsigned int nSamplesTaken = 0;
	int state = 0;
	std::string myStr("");
	
	if(!epocReady)
	{
		myStr.append("NO EPOC FOUND!");
		return myStr;
	}

	state = EE_EngineGetNextEvent(epocEvent);
	if(state == EDK_OK)
	{

		EE_Event_t eventType = EE_EmoEngineEventGetType(epocEvent);
		EE_EmoEngineEventGetUserId(epocEvent, &epocUserId);
		
		if(eventType == EE_UserAdded)
		{
			EE_DataAcquisitionEnable(epocUserId, true);
			EE_HeadsetGyroRezero(epocUserId);
		}

		EE_DataSetBufferSizeInSec(epocBufferInSecs);	// again?

		EE_DataUpdateHandle(0,hData);
		EE_DataGetNumberOfSample(hData, &nSamplesTaken);

		if( nSamplesTaken > 0 )
		{

			myStr.append("<emoData>");

			double* data = new double[nSamplesTaken];
			for(unsigned int sampleIdx = 0; sampleIdx < nSamplesTaken; ++sampleIdx)
			{

				myStr.append("<eeg ");
				int i = 0;
				for( i=0; i< (sizeof(targetChannelList)/sizeof(EE_DataChannel_t)-3) ; i++)
				{

					EE_DataGet(hData, targetChannelList[i], data, nSamplesTaken);
					myStr.append(EEGChannelNames[targetChannelList[i]]);
					myStr.append("=\'");
					stringstream dbtostr;
					dbtostr << data[sampleIdx];   
					
					myStr.append(dbtostr.str());
				
					myStr.append("\' ");

				}
				myStr.append("/>");

				myStr.append("<gyro ");

				for (i= (sizeof(targetChannelList)/sizeof(EE_DataChannel_t)-3); i< sizeof(targetChannelList)/sizeof(EE_DataChannel_t)-1; i++)
				{

					EE_DataGet(hData, targetChannelList[i], data, nSamplesTaken);
					myStr.append(EEGChannelNames[targetChannelList[i]]);
					myStr.append("=\'");
					
					stringstream dbtostr;
					dbtostr << data[sampleIdx];   
					
					myStr.append(dbtostr.str());
					myStr.append("\' ");
				
				}

				myStr.append("/>");

				myStr.append("<timestamp ");
				EE_DataGet(hData, targetChannelList[i], data, nSamplesTaken);
				myStr.append(EEGChannelNames[targetChannelList[i]]);
				myStr.append("=\'");
			
				stringstream dbtostr;
				dbtostr << data[sampleIdx];   
					
				myStr.append(dbtostr.str());
			
				myStr.append("\' ");
				myStr.append("/>");
			}

			delete [] data;

			if(eventType == EE_EmoStateUpdated)
			{

				myStr.append("<emotion ");
				EE_EmoEngineEventGetEmoState(epocEvent, epocState);

				if(ES_AffectivIsActive(epocState, AFF_ENGAGEMENT_BOREDOM)){
					myStr.append("engagement=\'");
					stringstream dbtostr;
					dbtostr << ES_AffectivGetEngagementBoredomScore(epocState);   
					
					myStr.append(dbtostr.str());
					
				}
				if(ES_AffectivIsActive(epocState, AFF_EXCITEMENT)){
					myStr.append("shortTermExcite=\'");
					stringstream dbtostr,ftostr;
					dbtostr << ES_AffectivGetExcitementShortTermScore(epocState);   
					
					myStr.append(dbtostr.str());
					ftostr << ES_AffectivGetExcitementLongTermScore(epocState);
					myStr.append("\' ");
					myStr.append("longTermExcite=\'");
					myStr.append(ftostr.str());
					myStr.append("\' ");
				}
				if(ES_AffectivIsActive(epocState, AFF_MEDITATION)){
					myStr.append("meditation='");
					stringstream dbtostr;
					dbtostr << ES_AffectivGetMeditationScore(epocState);   
					
					myStr.append(dbtostr.str());
					myStr.append("\' ");
				}
				if(ES_AffectivIsActive(epocState, AFF_FRUSTRATION)){
					myStr.append("frustration=\'");
					stringstream dbtostr;
					dbtostr << ES_AffectivGetFrustrationScore(epocState);   
					
					myStr.append(dbtostr.str());
					
					myStr.append("\' ");
				}
				myStr.append("/>");
			}

			myStr.append("</emoData>");
		}
	}else{

		//myStr.append("EPOC STATE NO DATA");
	}

	return myStr;

}

int ambient::initialize(int framesToSkip, unsigned int width, unsigned int height, float EPOC_BUFFER_SIZE_IN_SECONDS){

	this->framesToSkip = framesToSkip;

	// initialize our fullscreen grabber
	this->width = width;
	this->height = height;
	
//	::MessageBoxA(NULL, ("intialize"),("ambient plugin"), MB_OK);
	ambientLib = new Ambient(true,false,true,width,height);
	
	actualFrameCount = 0;

	// EPOC init section

	epocEvent = EE_EmoEngineEventCreate();
	epocState = EE_EmoStateCreate();

	epocReady = true;

	if(EE_EngineConnect() != EDK_OK)
	{
		epocReady = false;
		return -1; // failed to connect to EPOC EEG device
	}

	hData = EE_DataCreate();	// handle for the EEG data

	epocBufferInSecs = EPOC_BUFFER_SIZE_IN_SECONDS;
	EE_DataSetBufferSizeInSec(EPOC_BUFFER_SIZE_IN_SECONDS);

	epocUserId = 0;


	return 0;
}
#else

int ambient::initialize(int framesToSkip, unsigned int width, unsigned int height){

	this->framesToSkip = framesToSkip;

	// initialize our fullscreen grabber
	this->width = width;
	this->height = height;
	
	//::MessageBoxA(NULL, ("intialize"),("ambient plugin"), MB_OK);
	ambientLib = new Ambient(true,false,true,width,height);
	//::MessageBoxA(NULL, ("init done"),("ambient plugin"), MB_OK);
	
	actualFrameCount = 0;
	return 0;
}
#endif
int ambient::setCalculationRate(int pixelJump, int rowJump){

	ambientLib->setCACalculationRate( pixelJump, rowJump);
	return 0;
}

int ambient::calcFrame(){

	// tell the browser if we are ready to receive a frame
	if(framesToSkip > 0){

		actualFrameCount++;

		if(actualFrameCount > framesToSkip){
				actualFrameCount = 0;
			return 1;
		}else{
			return 0;
		}
	}else{
		// WOOHOO - WARP SPEED !
		return 1;
	}
	

}

unsigned int ambient::threadedCalculationFullscreen(){
	unsigned int ret_val = 0;
	// capture our screen

	screenHDC = GetDC(NULL);
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
	hdcMemory = CreateCompatibleDC(screenHDC);
	hbmMemory = CreateCompatibleBitmap(screenHDC,screenX,screenY);
	hbmOld = (HBITMAP) SelectObject(hdcMemory, hbmMemory);


	StretchBlt(hdcMemory,0,0,width,height,screenHDC,0,0,screenX,screenY,SRCCOPY);
	
	//BitBlt(hdcMemory,0,0,screenX,screenY,screenHDC,0,0,SRCCOPY);

	ZeroMemory(&bInfo, sizeof(BITMAPINFO));
	bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bInfo.bmiHeader.biWidth = width;
	bInfo.bmiHeader.biHeight = height;
	bInfo.bmiHeader.biBitCount = 24;
	bInfo.bmiHeader.biPlanes = 1;

	GetDIBits(hdcMemory, hbmMemory, 0, screenY, NULL, &bInfo,  DIB_RGB_COLORS);

	// now copy the image to our buffer

	// NOTE: it's an BGR frame ...

	unsigned char *data = (unsigned char *)malloc(bInfo.bmiHeader.biSizeImage);
	ret_val = bInfo.bmiHeader.biSizeImage;
	GetDIBits(hdcMemory,hbmMemory,0,height,data,&bInfo,DIB_RGB_COLORS);


	// now our frame calculation
	ret_val = ambientLib->lightFromPicture(data,IMAGE_FORMAT_BGR);
	
	SelectObject(hdcMemory, hbmOld);
	DeleteDC(hdcMemory);
	DeleteObject(hbmMemory);

	free(data);

	return ret_val;
	
}

int ambient::threadedCalculation(int width, int height, std::string &d){
	
	int ret_val = 0;
	// a workaround, because the npruntime doesn't allow to pass a js array by reference to a plugin ... (it's everytime a NPObject, where we can query every single elements)
	unsigned char *data = (unsigned char *)malloc(width * height * 4);
	int i=0;
	
	char * str = (char *)d.data();
	char *pch = strtok(str,";");
	while( pch != NULL) {
		data[i] = (unsigned char) atoi(pch);
		pch = strtok(NULL,";");
		i++;
	};
	

	ret_val = ambientLib->lightFromPicture(data,IMAGE_FORMAT_RGBA);
	
	
	free(data);
	
	return ret_val;		// to ensure that we fetched all pixel values
}

