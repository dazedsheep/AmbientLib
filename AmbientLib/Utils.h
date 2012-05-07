/*
 * Utils.h
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universität Klagenfurt
 *
 * Created on: April 9, 2011
 * Authors: Benjamin Rainer <benjamin.rainer@itec.aau.at>
 *			Markus Waltl	<markus.waltl@itec.aau.at>
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

#ifndef UTILS_H
#define UTILS_H

#include "stdafx.h"
#include <string>
#include <vector>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MIN_VOLUME	-5000
#define MAX_VOLUME	0
#define MUTE_VOLUME -10000
#define VOLUME_STEPPING	500

// convenient macro for releasing interfaces
#define HELPER_RELEASE(x)   if (x != NULL) \
                            { \
                                x->Release(); \
                                x = NULL; \
                            }

#define HUNDRET_MSEC 1000000.0
#define WM_GRAPHEVENT	WM_USER		// define a custom window message for graph events

class Utils
{
public:
	static long PercentToVolume(int percent);
	static int VolumeToPercent(long volume);
	static double Round(double number, int precision);
	static double Round(double value);
	static bool IsHex(std::string hexValue);
	static std::vector<std::string> StringSplit(std::string str, std::string delim);
	static int Clamp(int value, int lowerBound, int upperBound);
	static bool IsPathValid(char *path);
};

#endif