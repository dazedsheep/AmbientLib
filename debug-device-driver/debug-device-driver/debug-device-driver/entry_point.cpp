#include "stdafx.h"
#include "typedef.h"

#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include "Element.h"
#include "Classification.h"
#include "ptr.h"
#include "DeviceInterface.h"
#include "logger.h"
#include "AmBXLocationMap.h"
#include "Fan.h"
#include "Rumble.h"
#include "debugInterface.h"


#include "DeviceInterface.cpp"
#include "Classification.cpp"
#include "Element.cpp"
#include "Utils.cpp"


extern "C" __declspec(dllexport) DeviceInterface *ctor_a_InitDeviceDriver(bool disableFateTime, std::vector<Element*> elements)
{
	DeviceInterface *devI = new debugInterface(disableFateTime, elements);
	return devI;

}

extern "C" __declspec(dllexport) DeviceInterface *ctor_b_InitDeviceDriver(bool disableFateTime)
{

	DeviceInterface *devI = new debugInterface(disableFateTime);
	return devI;
}

extern "C" __declspec(dllexport) DeviceInterface *ctor_c_InitDeviceDriver(){

	DeviceInterface *devI = new debugInterface(false);
	return devI;

}