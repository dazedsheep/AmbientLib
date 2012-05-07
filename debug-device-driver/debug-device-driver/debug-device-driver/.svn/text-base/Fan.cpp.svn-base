#include "stdafx.h"
#include "Fan.h"

Fan::Fan()
{
	bFanFade = false;
	fanFadeTime = 0.0;
	fanEffectDifference = -1.0;
	fanOldIntensityValue = 0.0;
	fanDuration = -1.0;
	fanIntensity = 0.0;
	fanIntermediateIntensity = 0.0;
	fanPTS = 0.0;
	fanActive = false;
	
}

Fan::~Fan()
{
}

void Fan::resetFan()
{
	bFanFade = false;
	fanFadeTime = 0.0;
	fanEffectDifference = -1.0;
	fanOldIntensityValue = 0.0;
	fanDuration = -1.0;
	fanIntensity = 0.0;
	fanIntermediateIntensity = 0.0;
	fanPTS = 0.0;
	fanActive = false;
}

void Fan::setIntensityToDevice(float intensity)
{
	device_intensity = intensity;
}

float Fan::getIntensityFromDevice()
{
	return device_intensity;
}

bool Fan::isFanActive()
{
	return fanActive;
}

void Fan::activateFan(bool activate)
{
	fanActive = activate;
	if(activate)
	{
		// set the intensity back
		this->setIntensityToDevice((float)this->getIntensity());
	}
}

double Fan::getPTS() 
{ 
	return fanPTS; 
}
void Fan::setPTS(double time) 
{ 
	fanPTS = time; 
}

double Fan::getIntermediateIntensity()
{
	return fanIntermediateIntensity;
}

void Fan::setIntermediateIntensity(double intensity)
{
	fanIntermediateIntensity = intensity;
}

bool Fan::isFadeActive()
{
	return bFanFade;
}

void Fan::activateFade(bool activate)
{
	bFanFade = activate;
}

double Fan::getEffectDifference()
{
	return fanEffectDifference;
}

double Fan::getOldIntensityValue()
{
	return fanOldIntensityValue;
}

double Fan::getDuration()
{
	return fanDuration;
}

double Fan::getIntensity()
{
	return fanIntensity;
}

double Fan::getFadeTime()
{
	return fanFadeTime;
}

void Fan::setIntensity(double intensity)
{
	fanIntensity = intensity;
}

void Fan::setDuration(double duration)
{
	fanDuration = duration;
}

void Fan::setOldIntensityValue(double oldIntensity)
{
	fanOldIntensityValue = oldIntensity;
}

void Fan::setEffectDifference(double difference)
{
	fanEffectDifference = difference;
}

void Fan::setFadeTime(double fadeCount)
{
	fanFadeTime = fadeCount;
}
