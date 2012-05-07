/*
 * DeviceInterface.cpp
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

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Element.h"
#include "ptr.h"
#include "DeviceInterface.h"

bool DeviceInterface::playEffect(Element e)
{
	return false;
}

bool DeviceInterface::playEffectAtTime(double time)
{
	return false;
}

void DeviceInterface::colorToDevice(std::string loc, int r, int g, int b)
{

}

std::string DeviceInterface::getErrorString()
{
	return std::string("NYI");
}

bool DeviceInterface::hasError()
{
	return false;
}

void DeviceInterface::clearError()
{

}

void DeviceInterface::addEffect(Element *e)
{
}

void DeviceInterface::addEffects(std::vector<Element *> elements)
{

}

void DeviceInterface::getSupportedSensoryEffects(ptr<std::vector<int>> & vec)
{
}
std::vector<std::string> DeviceInterface::getLocations(int SUPPORTED)
{
	return std::vector<std::string>();
}

void DeviceInterface::displayColor()
{
}

void DeviceInterface::activateAllAvailableDevices(bool activate)
{
}

void DeviceInterface::activateDevice(unsigned int DEVICE, bool activate)
{

}

void DeviceInterface::activateAutoColor(bool activate)
{
}

void DeviceInterface::setVideoLength(double length)
{

}

double DeviceInterface::getVideoLength()
{
	return -1.0;

}