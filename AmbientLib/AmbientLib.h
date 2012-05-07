// AmbientLib.h : Hauptheaderdatei für die AmbientLib-DLL
//
#ifndef _AMBIENTLIB_H_
#define _AMBIENTLIB_H_
#ifdef _EXPORT_
#define DLL	__declspec(dllexport)
#else
#define DLL	__declspec(dllimport)
#endif

#define IMAGE_FORMAT_RGB		0x100
#define IMAGE_FORMAT_RGBA		0x200
#define IMAGE_FORMAT_ARGB		0x300
#define IMAGE_FORMAT_BGR		0x400
#define IMAGE_FORMAT_BGRA		0x500
#define IMAGE_INVALID_FORMAT	0x000


// Masks to identify which effects to activate/disable
#define EFFECTS_LIGHTS			100
#define EFFECTS_FANS			200
#define EFFECTS_RUMBLERS		300
#define EFFECTS_SCENT			400

#define	DEVICE_CONTEXT_ERROR					-1
#define	DEVICE_CONTEXT_ERROR_OPEN_PLUGIN_LIST	1
#define	DEVICE_CONTEXT_ERROR_LOADING_PLUGINS	2
#define	DEVICE_CONTEXT_ERROR_PLAYEFFECTATTIME	3
#define	DEVICE_CONTEXT_NO_ERROR					0

#define MAX_ERROR_MSGS			255

typedef struct _pair{
	const char *string[MAX_ERROR_MSGS];
	unsigned int size;
}pair;

class DLL Ambient
{

protected:
	void *myDC; // see DeviceContext.h
	void *cA; // see colorAlgorithm.h
	int activateAutoColor();
	unsigned int width,height;
	bool allowThreads;
private:
	double pts;
	bool effectsLoaded;
	bool autoColor;
	unsigned long timeScale;
public:
	
	
	Ambient(bool allowThreads,bool disableFateTime,bool enableAutoColor, unsigned int width, unsigned int height);
	~Ambient();

	bool isAutoColor();
	int setCACalculationRate(int pixelJump, int rowJump);
	int lightFromPicture(unsigned char *data, int PIXEL_FORMAT);
	bool playEffectAtTimeAbs(double);
	bool playEffectAtTimeRel(double);
	
	bool isEffectsLoaded();

	int reset();
	
	unsigned long getTimeScale();
	int loadSEMHTTP(const char *_url,const char *_SEMFile, bool directoryLookup);
	int loadSEMFromDisk(const char *SEMFile);
	int loadWithPreLoader(const char *file);
	
	int getDeviceContextErrorMessage();
	int getDeviceErrorMessages(pair &apair);
	int getErrorMessages(pair &pair);
	int activateAllDevices(bool activate);
	int activateDevice(unsigned int DEVICE, bool acticate);

	int setVideoLength(double length);

};

#endif