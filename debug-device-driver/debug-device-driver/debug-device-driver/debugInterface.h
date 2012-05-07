#ifndef _DEBUGINTERFACE_H_
#define _DEBUGINTERFACE_H_

class debugInterface : public DeviceInterface
{
private:
	double i_stime;
	double i_mtime;
	double add_tspan;
	bool zeroTime;
	Rumble rumble;
	Fan fan;
	std::ofstream file;
	AmBXLocationMap amBXLocationMap;
	std::vector<Element *> m_elements;
	void fadeVibration(double time, Rumble *rumble);
	void fadeWind(double time, Fan* fan);
	void handleWind(Element e);
	void handleVibration(Element e);
	bool isInIntensityRange(double value, std::vector<std::string> range); 
public:
	debugInterface(bool disableFateTime, std::vector<Element*> elements);
	debugInterface(bool disableFateTime);
	~debugInterface();
	void getSupportedSensoryEffects(ptr<std::vector<int>> & vec);
	void createLoggingWindow();
	void colorToDevice(std::string, int r, int g, int b);
	void displayColor();

	bool playEffectAtTime(double time);
	void addEffects(std::vector<Element*> elements);
	bool playEffect(Element e);
	HWND logWindow;
	_log::logger log;
};

#endif