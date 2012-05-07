#ifndef RUMBLE_H
#define RUMBLE_H

class Rumble
{
public:
	Rumble();
	~Rumble();

	
	bool isFadeActive();
	bool isRumbleActive();
	double getEffectDifference();
	double getOldIntensityValue();
	double getDuration();
	double getIntensity();
	double getFadeTime();
	double getIntermediateIntensity();
	double getPTS();
	void activateRumble(bool activate);
	void setIntensity(double intensity);
	void setDuration(double duration);
	void setOldIntensityValue(double oldIntensity);
	void setEffectDifference(double difference);
	void setFadeTime(double fadeCount);
	void activateFade(bool activate);
	void setIntermediateIntensity(double intensity);
	void setPTS(double time);
	void resetRumble();


	// devices settings

	void setIntensityToDevice(float intensity);
	float getIntensityFromDevice();


private:
	
	double device_intensity;

	bool bRumbleFade;
	bool rumbleActive;
	double rumbleFadeTime;
	double rumbleEffectDifference;
	double rumbleOldIntensityValue;
	double rumbleDuration;
	double rumbleIntensity;
	double rumbleIntermediateIntensity;
	double rumblePTS;
};

#endif