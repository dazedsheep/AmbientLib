#include "stdafx.h"

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "typedef.h"
#include "Element.h"
#include "Classification.h"
#include "ptr.h"
#include "DeviceInterface.h"
#include "logger.h"
#include "Utils.h"
#include "AmBXLocationMap.h"
#include "Fan.h"
#include "Rumble.h"


#include "debugInterface.h"




#define EFFECT_TIME_SPAN					0.15f
#define EFFECT_TIME_SPAN_ERROR_CORRECTION	0.05f
#define EFFECT_TIME_SPAN_MAX				0.3f	

ptr<debugInterface> o_dI;
RECT rect[9];

typedef struct {
	char r, g, b;
}rectColor;

typedef struct
{
	RECT rect;
	float intensity;
}dev;

rectColor rectCol[10];
dev windgens[2];
dev vibration[1];

LRESULT CALLBACK windowProc(HWND hwnd, UINT u_msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch(u_msg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETTEXT:
		break;

	case WM_PAINT:
		
		
		hdc = BeginPaint(hwnd,&ps);
		
		for(unsigned int i=0;i<9;i++)
		{
	
			HBRUSH tc = CreateSolidBrush(RGB(rectCol[i].r,rectCol[i].g,rectCol[i].b));
			FillRect(hdc, &rect[i],tc);
			FrameRect(hdc, &rect[i],(HBRUSH)GetStockObject(BLACK_BRUSH));
			DeleteObject(tc);
		}

		for(unsigned int i=0;i<2;i++)
		{
			HBRUSH tc = CreateSolidBrush(RGB(0,0,255));
			RECT _r = windgens[i].rect;
			_r.top = _r.bottom - (LONG)(_r.bottom*windgens[i].intensity);
			FillRect(hdc, &_r,tc);
			FrameRect(hdc, &windgens[i].rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
			DeleteObject(tc);
		}
		{
		HBRUSH tc = CreateSolidBrush(RGB(0,255,0));
		RECT _r = vibration[0].rect;
		_r.right = _r.left + (LONG) (_r.right*vibration[0].intensity);
		FillRect(hdc, &_r,tc);
		FrameRect(hdc, &vibration[0].rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
		DeleteObject(tc);
		EndPaint(hwnd, &ps);
		}
		break;
	
	default: 	return DefWindowProc(hwnd,u_msg,wParam, lParam);
	}
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID param)
{
	MSG msg;
	WNDCLASSEX wndCL;

	HINSTANCE hInstance = GetModuleHandle("debug-device-driver.dll");

	if (hInstance == NULL) std::cout << "can't retrieve module handle" << std::endl;
	else
		std::cout << "Found handle of the module!" << std::endl;
	ZeroMemory(&wndCL, sizeof(wndCL));
	wndCL.hInstance = hInstance;
	wndCL.lpszClassName = "DebugDeviceDriverClass";
	wndCL.lpfnWndProc = windowProc;
	wndCL.cbSize = sizeof(WNDCLASSEX);
	wndCL.style = CS_DBLCLKS;
	wndCL.hCursor = LoadCursor (NULL, IDC_ARROW);
	wndCL.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	if(!RegisterClassEx(&wndCL)) return 0;

	ptr<debugInterface> dI(param);
	dI->logWindow = CreateWindowEx(NULL, "DebugDeviceDriverClass","Debug Device Driver Simulator Window", WS_EX_PALETTEWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

	ShowWindow(dI->logWindow, SW_SHOWNORMAL);

	while(GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	
	return 1;
}

debugInterface::debugInterface(bool disableFateTime, std::vector<Element*> elements)
{
	// create the file for debugging
	o_dI = this;
	m_elements = elements;
	createLoggingWindow();

}

debugInterface::debugInterface(bool disableFateTime)
{
	o_dI = this;
	createLoggingWindow();
}

debugInterface::~debugInterface()
{
	SendMessage(logWindow,WM_DESTROY,0,0); 
}

void debugInterface::getSupportedSensoryEffects(ptr<std::vector<int>> &vec)
{

	vec->push_back(DEVICE_SUPPORTS_LIGHTS);
	vec->push_back(DEVICE_SUPPORTS_FANS);
	vec->push_back(DEVICE_SUPPORTS_RUMBLERS);

}


void debugInterface::createLoggingWindow()
{
	unsigned int width = 400, height = 300, size=60; 
	int n=-1;
	unsigned int dleft = width/2 - (3*size + 10)/2;
	for (unsigned int i=0;i<9;i++)
	{
		if(i%3==0) n++;

		
		rect[i].left = dleft + ((i%3 * size) + (i%3 * 5));
		rect[i].bottom = size + (n*size + n*5);
		rect[i].right = dleft + size + ((i%3 * size) + (i%3 * 5));
		rect[i].top = 0 + (n*size + n*5);

	}

	// set the wind bars
	windgens[0].rect.left = 10;
	windgens[0].rect.bottom = 3*size+10;
	windgens[0].rect.right = 50;
	windgens[0].rect.top = 0;
	windgens[0].intensity = 0.0f;

	windgens[1].rect.left = width - 50;
	windgens[1].rect.bottom = 3*size+10;
	windgens[1].rect.right = width - 10;
	windgens[1].rect.top = 0;
	windgens[1].intensity = 0.0f;

	// set the vibration bars
	vibration[0].intensity = 0.0f;
	vibration[0].rect.left = 10;
	vibration[0].rect.bottom = height-10;
	vibration[0].rect.right = width -10;
	vibration[0].rect.top = height - 40;

	CreateThread( 0, NULL, ThreadFunc, this, NULL, NULL);

}

void debugInterface::colorToDevice(std::string str, int r, int g, int b)
{
	int clampedColorR = Utils::Clamp(r, 0, 255);
	int clampedColorG = Utils::Clamp(g, 0, 255);
	int clampedColorB = Utils::Clamp(b, 0, 255);
	

	std::vector<amBX_loc> locations = amBXLocationMap.getAmBXLocations(str);
	if(locations.size() >0)
	{
		
		for(unsigned int i=0;i<locations.size(); i++)
		{
			rectCol[locations.at(i)].r = clampedColorR;
			rectCol[locations.at(i)].g = clampedColorG;
			rectCol[locations.at(i)].b = clampedColorB;
		}
		InvalidateRect(logWindow, NULL, TRUE); 
	}

}

void debugInterface::displayColor()
{
//	SendMessage(logWindow, WM_SETTEXT, 0,0);
}

bool debugInterface::playEffectAtTime(double time)
{
	bool played = false;

	// check when we were called last, if this intervall is bigger than our 100ms then try to adjust the time span
	// if the current timestamp is lower than the last, reset 
	if(time < i_mtime || !zeroTime)
	{
		add_tspan = 0.0;
	}
    else
    {

		// calc the missing portion
		if(time - i_mtime > EFFECT_TIME_SPAN) 
		{
				add_tspan = (time - i_mtime) - EFFECT_TIME_SPAN + EFFECT_TIME_SPAN_ERROR_CORRECTION;	// add a little error correction, so we can be sure that we don't miss any effect
				// in worst case scenarios we may get here seconds ...
				// prevent this by checking for a maximum additional time spam
				if(add_tspan+EFFECT_TIME_SPAN > EFFECT_TIME_SPAN_MAX) 
                    add_tspan = EFFECT_TIME_SPAN_MAX - EFFECT_TIME_SPAN;
		}
		
		if(time - i_mtime <= EFFECT_TIME_SPAN) 
            add_tspan = 0.0;	// we are within the time span of 100ms, we won't need to check further backwards
		
	}
	
	for (std::vector<Element*>::const_iterator it = m_elements.begin(); it != m_elements.end(); ++it)
	{
		// if we rewind the movie and the effects have already been played, we have to reset their timestamp
		if(time < (*it)->getPlayedTime()) 
            (*it)->setPlayedTime(-1.0);

		// do we have played the effect already ?
		
		if((*it)->getPlayedTime() < 0.0f)
		{
			if ((*it)->getTime() == 0.0 && !zeroTime)
			{
				(*it)->setPlayedTime(time);
				played = playEffect(*(*it));
			}
            else if ((*it)->getTime() >= time-(EFFECT_TIME_SPAN+add_tspan) && (*it)->getTime() <= time)
			{
				(*it)->setPlayedTime(time);
				played = playEffect(*(*it));	
			}
		}
	}
	i_mtime = time;		// save our timestamp
	zeroTime = true;

	// play fade
	if (rumble.isFadeActive())
		fadeVibration(time, &rumble);
	
	
	if (fan.isFadeActive())
		fadeWind(time, &fan);
	


	windgens[1].intensity = windgens[0].intensity = fan.getIntensityFromDevice() * 0.01f;
	vibration[0].intensity = rumble.getIntensityFromDevice() * 0.01f;


	InvalidateRect(logWindow, NULL, TRUE); 


	return played;
}

void debugInterface::addEffects(std::vector<Element*> elements)
{
	this->m_elements = elements;
}


bool debugInterface::playEffect(Element e)
{
	//e.print();
	switch (e.getType())
	{
	case TYPE_FAN:
		handleWind(e);
		break;
	case TYPE_VIBRATOR:
		handleVibration(e);
		break;
	case TYPE_LIGHT:
		//handleLight(e);
		break;
	case TYPE_WATERSPRAYER:
	case TYPE_AIRCONDITIONER:
	case TYPE_FOG:
		// not needed/used
		break;
	case TYPE_PERFUMER:
		// will be implemented soon
		break;
	case TYPE_NONE:
	default:
		return false;
	}

	/*char msg[100];
	sprintf(msg, "type: %i; time: %.1f", e.getType(), e.getTime());*/
	return true;
}


void debugInterface::fadeWind(double time, Fan *fan)
{
	if ((time-EFFECT_TIME_SPAN) < (fan->getPTS() + fan->getFadeTime())) 
	{
		
	
		fan->setIntensity(fan->getIntermediateIntensity() + ((fan->getEffectDifference() / fan->getFadeTime()) * (time - fan->getPTS())));
			
		if (fan->getIntensity() > -1.0)
			 fan->setIntensityToDevice((float)fan->getIntensity());
		
		if (fan->getDuration() > 0)
		{
			fan->setDuration(fan->getDuration() - (time - fan->getPTS()));
			if (fan->getDuration() <= 0)
			{
				 fan->setIntensityToDevice(0.0f);
			}
		}
	}
}

bool debugInterface::isInIntensityRange(double value, std::vector<std::string> range) 
{
	if (!range.empty()) 
	{
		if (range.size() == 2) {
			double lower = atof(range.at(0).c_str());
			double upper = atof(range.at(1).c_str());
			if (lower > value || upper < value) 
			{
				printf("Intensity value is outside of the intensity range! Aborting!");
				return false;
			}
		}
		else
			printf("Intensity range is not given correctly!");
	}
	return true;
}


void debugInterface::fadeVibration(double time, Rumble *rumble)
{
	if ((time-EFFECT_TIME_SPAN) < (rumble->getPTS() + rumble->getFadeTime())) 
	{
			
		rumble->setIntensity(rumble->getIntermediateIntensity() + ((rumble->getEffectDifference() / rumble->getFadeTime())*(time - rumble->getPTS())));
		
		if (rumble->getIntensity() > -1.0)
			rumble->setIntensityToDevice((float)rumble->getIntensity());

		if (rumble->getDuration() > 0)
		{
			rumble->setDuration(rumble->getDuration() - (time - rumble->getPTS()));
			if(rumble->getDuration() <= 0)
			{
				rumble->setIntensityToDevice(0.0f);
			}
		}
	}
}

void debugInterface::handleWind(Element e)
{
	if (strcmp(e.getValue(ATT_GEN_ACTIVATE).c_str(), SEMP_TRUE) == 0)
	{
		std::vector<std::string> range;

		if (!strcmp(e.getValue(ATT_INTENSITYRANGE).c_str(), "") == 0)
		{
			range = Utils::StringSplit(e.getValue(ATT_INTENSITYRANGE), " ");
			if (!isInIntensityRange(atof(e.getValue(ATT_INTENSITYVALUE).c_str()), range))
				return;
		}
		double fanPTS = e.getPlayedTime();	// when was our effect played
		double fanFade = atof(e.getValue(ATT_GEN_FADE).c_str());
		double fanDuration = atof(e.getValue(ATT_GEN_DURATION).c_str());
		double fanIntensity = atof(e.getValue(ATT_INTENSITYVALUE).c_str());

		// calculate the percentage of intensity
		if (range.size() == 2)
		{
			double upperBound = atof(range.at(1).c_str());
			fanIntensity = (100.0 / upperBound) * fanIntensity;
		}

		// check if fade is not bigger than duration
		if (fanFade != 0 && fanDuration != 0)
		{
			if (fanFade > fanDuration) 
			{
				printf("Fade cannot be bigger than the duration of effect! Aborting!");
				return;
			}
		}

		if (strcmp(e.getValue(ATT_GEN_LOCATION).c_str(), "") != 0)
		{
			
			fan.setFadeTime(fanFade);
			fan.setDuration(fanDuration);
			fan.setIntensity(fanIntensity);
			fan.setPTS(fanPTS);

					if (fanFade > 0) 
					{
						fan.activateFade(true);
						if (fan.getOldIntensityValue() > 0)
						{
							fan.setEffectDifference(fan.getIntensity() - fan.getOldIntensityValue());
							fan.setIntermediateIntensity(fan.getOldIntensityValue());
						}else{
							fan.setIntermediateIntensity(0.0);
							fan.setEffectDifference(fan.getIntensity());
						}
					}
					else
						fan.activateFade(false);

					fan.setOldIntensityValue(fan.getIntensity());
					
					if (!fan.isFadeActive())
						fan.setIntensityToDevice((float)fan.getIntensity());
					
					
					
				
		}
		else
		{
			
				
					fan.setFadeTime(fanFade);
					fan.setDuration(fanDuration);
					fan.setIntensity(fanIntensity);
					fan.setPTS(fanPTS);

					// calculate stepping
					if (fanFade > 0) 
					{
						fan.activateFade(true);
						if (fan.getOldIntensityValue() > 0)
						{
							fan.setEffectDifference(fan.getIntensity() - fan.getOldIntensityValue());
							fan.setIntermediateIntensity(fan.getOldIntensityValue());
						}
						else
						{
							fan.setIntermediateIntensity(0.0);
							fan.setEffectDifference(fan.getIntensity());
						}
					}
					else
						fan.activateFade(false);

					fan.setOldIntensityValue(fan.getIntensity());
		
					// forward the effect to the device if and only if the fan is active
					if (!fan.isFadeActive())
						fan.setIntensityToDevice((float)fan.getIntensity());
					
					
					
		}		
	}
	else if (strcmp(e.getValue(ATT_GEN_ACTIVATE).c_str(), SEMP_FALSE) == 0)
	{
		if (strcmp(e.getValue(ATT_GEN_LOCATION).c_str(), "") != 0)
		{
			fan.activateFade(false);
			fan.setIntensityToDevice(0.0f);
			
			
		}
	}
}

void debugInterface::handleVibration(Element e)
{
	if (strcmp(e.getValue(ATT_GEN_ACTIVATE).c_str(), SEMP_TRUE) == 0)
	{
		std::vector<std::string> range;

		if (!strcmp(e.getValue(ATT_INTENSITYRANGE).c_str(), "") == 0)
		{
			range = Utils::StringSplit(e.getValue(ATT_INTENSITYRANGE), " ");
			if (!isInIntensityRange(atof(e.getValue(ATT_INTENSITYVALUE).c_str()), range))
				return;
		}

		double rumblePTS = e.getPlayedTime();
		double rumbleFade = atof(e.getValue(ATT_GEN_FADE).c_str());
		double rumbleDuration = atof(e.getValue(ATT_GEN_DURATION).c_str());
		double rumbleIntensity = atof(e.getValue(ATT_INTENSITYVALUE).c_str());

		// calculate the percentage of intensity
		if (range.size() == 2)
		{
			double upperBound = atof(range.at(1).c_str());
			rumbleIntensity = (100.0 / upperBound) * rumbleIntensity;
		}

		// check if fade is not bigger than duration
		if (rumbleFade != 0 && rumbleDuration != 0)
		{
			if (rumbleFade > rumbleDuration) 
			{
				printf("Fade cannot be bigger than the duration of effect! Aborting!");
				return;
			}
		}

		if (strcmp(e.getValue(ATT_GEN_LOCATION).c_str(), "") != 0)
		{
			rumble.setFadeTime(rumbleFade);
			rumble.setDuration(rumbleDuration);
					rumble.setIntensity(rumbleIntensity);
					rumble.setPTS(rumblePTS);

					// calculate stepping
					if (rumbleFade > 0) 
					{
						rumble.activateFade(true);
						if (rumble.getOldIntensityValue() > 0)
						{
							rumble.setEffectDifference(rumble.getIntensity() - rumble.getOldIntensityValue());
							rumble.setIntermediateIntensity(rumble.getOldIntensityValue());
						}
						else
						{
							rumble.setIntermediateIntensity(0.0);
							rumble.setEffectDifference(rumble.getIntensity());
						}
					}
					else
						rumble.activateFade(false);

					rumble.setOldIntensityValue(rumble.getIntensity());

				
					if (!rumble.isFadeActive())
						rumble.setIntensityToDevice((float)rumble.getIntensity());

				
		}
		else
		{
			// get all location
			// activate all
					rumble.setFadeTime(rumbleFade);
					rumble.setDuration(rumbleDuration);
					rumble.setIntensity(rumbleIntensity);
					rumble.setPTS(rumblePTS);

					// calculate stepping
					if (rumbleFade > 0) 
					{
						rumble.activateFade(true);
						if (rumble.getOldIntensityValue() > 0)
						{
							rumble.setEffectDifference(rumble.getIntensity() - rumble.getOldIntensityValue());
							rumble.setIntermediateIntensity(rumble.getOldIntensityValue());
						}
						else
						{
							rumble.setIntermediateIntensity(0.0);
							rumble.setEffectDifference(rumble.getIntensity());
						}
					}
					else
						rumble.activateFade(false);

					rumble.setOldIntensityValue(rumble.getIntensity());

					if (!rumble.isFadeActive())
						rumble.setIntensityToDevice((float)rumble.getIntensity());

			
		}
	}
	else if (strcmp(e.getValue(ATT_GEN_ACTIVATE).c_str(), SEMP_FALSE) == 0)
	{
		if (strcmp(e.getValue(ATT_GEN_LOCATION).c_str(), "") != 0)
		{
			
					
					rumble.setIntensityToDevice(0.0f);
					rumble.activateFade(false);
					
			
		}
	}
}
