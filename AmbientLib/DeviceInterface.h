/*
 * DeviceInterface.h
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
#ifndef DEVICE_INTERFACE_H_
#define DEVICE_INTERFACE_H_


// THIS LIST MUST MATCH THE LIST IN AMBIENTLIB.H !
#define DEVICE_SUPPORTS_LIGHTS		100
#define DEVICE_SUPPORTS_FANS		200
#define DEVICE_SUPPORTS_RUMBLERS	300
#define DEVICE_SUPPORTS_SCENT		400
#define DEVICE_SUPPORTS_WATER		500
#define DEVICE_SUPPORTS_FOG			600
// ... future extensions


class DeviceInterface {

public:
	virtual ~DeviceInterface(){};
	
	virtual void setVideoLength(double length);
	virtual double getVideoLength();


	// play effects
	virtual bool playEffect(Element e);
	virtual bool playEffectAtTime(double time);
	
	// show color
	virtual void colorToDevice(std::string, int r, int g, int b);
	virtual void displayColor();

	// activate / deactivate all devices 
	virtual void activateAllAvailableDevices(bool activate);
	virtual void activateDevice(unsigned int DEVICE, bool activate);
	virtual void activateAutoColor(bool activate);

	// error handling
	virtual std::string getErrorString();
	virtual bool hasError();
	virtual void clearError();
	
	// adding effects to the device driver
	virtual void addEffect(Element *e);
	virtual void addEffects(std::vector<Element*> elements);

	// check which devices are supported
	virtual void getSupportedSensoryEffects(ptr<std::vector<int>> & vec);
	
	// function to retrieve the locations of the devices
	virtual std::vector<std::string> getLocations(int SUPPORTED);
	
};


#ifdef DEVICE_DRIVER_IMPLEMENTATION
extern "C" __declspec(dllexport) DeviceInterface *ctor_a_InitDeviceDriver(bool disableFateTime, std::vector<Element*> elements);
extern "C" __declspec(dllexport) DeviceInterface *ctor_b_InitDeviceDriver(bool disableFateTime);
extern "C" __declspec(dllexport) DeviceInterface *ctor_c_InitDeviceDriver();
#else
typedef DeviceInterface* (*ctor_a_InitDeviceDriver)(bool disableFateTime, std::vector<Element*> elements);
typedef DeviceInterface* (*ctor_b_InitDeviceDriver)(bool disableFateTime);
typedef DeviceInterface* (*ctor_c_InitDeviceDriver)();
#endif

#endif