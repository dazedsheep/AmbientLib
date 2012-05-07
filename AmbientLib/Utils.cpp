/*
 * Utils.cpp
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
#include "Utils.h"

double Utils::Round(double number, int precision)
{
	number *= pow(10.0, precision);
	if (number >= 0)
		number = floor(number + 0.5);
	else
		number = ceil(number - 0.5);

	number /= pow(10.0, precision);

	return number;
}

double Utils::Round(double value)
{
	return floor(value + 0.5);
}

int Utils::VolumeToPercent(long volume)
{
	return (volume - MIN_VOLUME) / ((MAX_VOLUME - MIN_VOLUME) / 100);
}

long Utils::PercentToVolume(int percent)
{
	return MIN_VOLUME + (percent * ((MAX_VOLUME - MIN_VOLUME) / 100));
}

bool Utils::IsHex(std::string hexValue)
{
	if (hexValue.length() == 6)
	{
		char cpHex [8];
		strcpy_s(cpHex, sizeof(cpHex), hexValue.c_str());
		char* nextToken = NULL;
		char* token = strtok_s(cpHex, "0123456789ABCDEFabcdef", &nextToken);
		return (token == NULL);
	}
	else
		return false;
}

int Utils::Clamp(int value, int lowerBound, int upperBound)
{
	if(value > upperBound || value < lowerBound)
	{
		if(value > upperBound) 
			value = upperBound;
		else
			value = lowerBound;
	}
	
	return value;
}

/*
method taken from http://www.computing.net/answers/programming/string-split-for-c/13456.html
*/
std::vector<std::string> Utils::StringSplit(std::string str, std::string delim)
{
	std::vector<std::string> results;
	int cutAt;
	while( (cutAt = str.find_first_of(delim)) != str.npos )
	{
		if(cutAt > 0)
		{
			results.push_back(str.substr(0,cutAt));
		}
		str = str.substr(cutAt+1);
	}
	
	if(str.length() > 0)
	{
		results.push_back(str);
	}

	return results;
}

bool Utils::IsPathValid(char *path)
{
	bool retVal = false;
	if (_access(path, 0) == 0)
	{
		struct stat status;
		stat(path, &status);

		if (status.st_mode & S_IFDIR)
		{
			retVal = true;
		}
	}

	return retVal;
}
