#ifndef FAN_H
#define FAN_H



class Fan
{
public:
	Fan();
	~Fan();
	bool isFadeActive();
	bool isFanActive();
	double getEffectDifference();
	double getOldIntensityValue();
	double getDuration();
	double getIntensity();
	double getFadeTime();
	double getIntermediateIntensity();
	double getPTS();
	void activateFan(bool activate);
	void setIntensity(double intensity);
	void setDuration(double duration);
	void setOldIntensityValue(double oldIntensity);
	void setEffectDifference(double difference);
	void setFadeTime(double fadeCount);
	void activateFade(bool activate);
	void setIntermediateIntensity(double intensity);
	void setPTS(double time);
	void resetFan();

	// devices settings

	void setIntensityToDevice(float intensity);
	float getIntensityFromDevice();


private:

	double device_intensity;

	bool bFanFade;
	bool fanActive;
	double fanFadeTime;
	double fanEffectDifference;
	double fanOldIntensityValue;
	double fanDuration;
	double fanIntensity;
	double fanIntermediateIntensity;
	double fanPTS;
};

#endif