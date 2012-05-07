/*
 * DebugAmbientLib.cpp
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universitšt Klagenfurt
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

#ifndef DEBUG_AMBIENTLIB_H_
#define DEBUG_AMBIENTLIB_H_

class DLL DebugAmbient : public Ambient
{
public:
	DebugAmbient(bool allowThreads,bool disableFateTime, bool enableAutoColor, unsigned int width, unsigned int height);

	~DebugAmbient(void);

	// some useful things
	bool forceColorAlgorithmCPUSupport(bool set);
	bool colorAlgorithmHasCPUSupport();
	bool colorAlgorithmUsesCPUSupport();
	void testHTTP();
	void testDeviceContextCreate();
	void testDeviceContextClose();
	void runEffectAnalysis(const char *path,unsigned int length);
	void testScreenSplitter(unsigned int x, unsigned int y);
};

#endif