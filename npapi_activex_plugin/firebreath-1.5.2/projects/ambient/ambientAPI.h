/**********************************************************\

  Auto-generated ambientAPI.h
  
\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "ambient.h"

#ifndef H_ambientAPI
#define H_ambientAPI

#define MOZILLA_FIREFOX		0
#define GOOGLE_CHROME		1
#define OPERA				2
#define MICROSOFT_IE		3
#define SAFARI				4

#define AUTO_FETCH			10

class ambientAPI : public FB::JSAPIAuto
{
public:
    ambientAPI(const ambientPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~ambientAPI();

    ambientPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(fired, 3, (const FB::variant&, bool, int));
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));
    FB_JSAPI_EVENT(notify, 0, ());

    // Method test-event
    void testEvent(const FB::variant& s);

	int getErrorMessage();

	int setCalculationRate(int pixelJump, int rowJump);
	int threadedCalculation(int width, int height, std::string &d);
	int calcFrame();
#ifdef USE_EPOC
	std::string queryEPOC();
	int initialize(int framesToSkip, unsigned int width, unsigned int height, float EPOC_BUFFER_SIZE_IN_SECS);
#else
	int initialize(int framesToSkip,unsigned int width, unsigned int height);
#endif
	unsigned long t();
	unsigned int threadedCalculationFullscreen();
	
	void loadSEM(std::string url, std::string file);
	void playEffectAtTimeAbs(double time);
	void playEffectAtTimeRel(double time);
	unsigned int getWidth(unsigned int width, unsigned int height);
	unsigned int getHeight();
	unsigned int grabFrame(unsigned int webBrowser, unsigned int scwidth, unsigned scheight, unsigned int widht, unsigned int height);

private:
    

	ambientWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
	
	
};

#endif // H_ambientAPI

