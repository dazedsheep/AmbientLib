#include "stdafx.h"
#include "Rumble.h"

Rumble::Rumble()
{
	bRumbleFade = false;
	rumbleFadeTime = -1.0;
	rumbleEffectDifference = -1.0;
	rumbleOldIntensityValue = 0.0;
	rumbleDuration = -1.0;
	rumbleIntensity = 0.0;
	rumblePTS = 0.0;
	rumbleIntermediateIntensity = 0.0;
	rumbleActive = false;
	
}

Rumble::~Rumble()
{
}

void Rumble::resetRumble()
{
	bRumbleFade = false;
	rumbleFadeTime = -1.0;
	rumbleEffectDifference = -1.0;
	rumbleOldIntensityValue = 0.0;
	rumbleDuration = -1.0;
	rumbleIntensity = 0.0;
	rumblePTS = 0.0;
	rumbleIntermediateIntensity = 0.0;
}


void Rumble::setIntensityToDevice(float intensity)
{
	device_intensity = intensity;
}

float Rumble::getIntensityFromDevice()
{
	return device_intensity;
}

bool Rumble::isRumbleActive()
{
	return rumbleActive;
}

void Rumble::activateRumble(bool activate)
{
	rumbleActive = activate;
	if(activate)
	{
		this->setIntensityToDevice((float)this->getIntensity());
	}
}

double Rumble::getPTS()
{ 
	return rumblePTS; 
}
void Rumble::setPTS(double time)
{ 
	rumblePTS = time;
}

double Rumble::getIntermediateIntensity()
{
	return rumbleIntermediateIntensity;
}

void Rumble::setIntermediateIntensity(double intensity)
{
	rumbleIntermediateIntensity = intensity;
}

bool Rumble::isFadeActive()
{
	return bRumbleFade;
}

void Rumble::activateFade(bool activate)
{
	bRumbleFade = activate;
}

double Rumble::getEffectDifference()
{
	return rumbleEffectDifference;
}

double Rumble::getOldIntensityValue()
{
	return rumbleOldIntensityValue;
}

double Rumble::getDuration()
{
	return rumbleDuration;
}

double Rumble::getIntensity()
{
	return rumbleIntensity;
}

double Rumble::getFadeTime()
{
	return rumbleFadeTime;
}

void Rumble::setIntensity(double intensity)
{
	rumbleIntensity = intensity;
}

void Rumble::setDuration(double duration)
{
	rumbleDuration = duration;
}

void Rumble::setOldIntensityValue(double oldIntensity)
{
	rumbleOldIntensityValue = oldIntensity;
}

void Rumble::setEffectDifference(double difference)
{
	rumbleEffectDifference = difference;
}

void Rumble::setFadeTime(double fadeTime)
{
	rumbleFadeTime = fadeTime;
}
