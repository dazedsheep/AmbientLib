/*
 * DeviceContext.h
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universität Klagenfurt
 *
 * Created on: April 9, 2011
 * Authors: Benjamin Rainer <benjamin.rainer@itec.aau.at>
 *
 * This file is part of ambientLib.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef DEVICE_CONTEXT_H_
#define DEVICE_CONTEXT_H_

#define LOAD_DRIVER							1

// error states
#define		DEVICE_ERROR					-1
#define		DEVICE_ERROR_OPEN_DRIVER_LIST	1
#define		DEVICE_ERROR_LOADING_DRIVERS	2
#define		DEVICE_ERROR_PLAYEFFECTATTIME	3
#define		DEVICE_NO_ERROR					0

class DeviceContext
{
private:

//	std::vector<DeviceInterface *> devices;
//	std::vector<ptr<std::vector<int>>> supportedTypes;
	std::map<DeviceInterface *,ptr<std::vector<int>>> devices;	// this vector holds all initialized devices
	std::vector<HINSTANCE> loadedPlugins;
	int errorMessage;
	double last_timestamp;
public:
	DeviceContext(bool disableFateTime);
	DeviceContext(bool disableFateTime, std::vector<Element *> elements);
	DeviceContext();
	~DeviceContext(void);

	int	getErrorMessage();
	std::vector<std::string> getDeviceErrors();
	int AddEffectsToDevices(std::vector<Element *> elements);
	bool playEffectAtTime(double time);
	
	void colorToDevice(std::string, int r, int g, int b);
	void devicesDisplayColor();
	void activateDevice(unsigned int DEVICE, bool activate);
	void activateAllAvailableDevices(bool activate);
	void activateAutoColor(bool activate);

	void setVideoLength(double length);
	
};



DeviceContext *GetDeviceContext();
DeviceContext *GetDeviceContext(bool disableFateTime,std::vector<Element *> elements);
DeviceContext *GetDeviceContext(bool disableFateTime);
void ReleaseDeviceContext();

#endif