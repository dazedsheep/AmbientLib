/*
 * ScreenSplitter.cpp
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

#include "StdAfx.h"
#include <Windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <map>
#include "Classification.h"
#include "ScreenSplitter.h"

using namespace AmbientLib;

ScreenSplitter::ScreenSplitter(unsigned int width, unsigned int height)
{

	// calculate the splitting and pre calculate where the pixels go
	// create a pixel indexed memory location
	// note: we have to avoid divison by 0
	// calculate the straight lines, we have 4 of them

	// center of our frame 
	mx= floor((double)width/2);
	my= floor((double)height/2);
	this->width = width;
	this->height = height;
	
	p1.x = (width * WIDTH_SPLITTING) * NWNESWSE_PIECES;
	p1.y = 0;

	p2.x = p1.x + (width * WIDTH_SPLITTING) * NS_PIECES;
	p2.y = 0;

	p3.x = 0;
	p3.y = (height * HEIGHT_SPLITTING) * NWNESWSE_PIECES;
	
	p4.x = 0;
	p4.y = p3.y + (height * HEIGHT_SPLITTING) * WE_PIECES;

	g1.p = p1;
	g1.m = (my - p1.y) / (mx - p1.x);
	g1.n = p1.y - (g1.m*p1.x);

	g2.p = p2;
	g2.m = (my - p2.y) / (mx - p2.x);
	g2.n = p2.y - (g2.m*p2.x);

	g3.p = p3;
	g3.m = (my - p3.y) / (mx - p3.x);
	g3.n = p3.y - (g3.m*p3.x);

	g4.p = p4;
	g4.m = (my - p4.y) / (mx - p4.x);
	g4.n = p4.y - (g4.m*p4.x);


	// now we can build up our indexed memory
	// we have 9 locations defined in the standard, we may omit the center for now

	
	mem = (unsigned char *) malloc(width * height * sizeof(unsigned char));
	memset(mem,0,width * height * sizeof(unsigned char));
	for(unsigned int y=0; y<height;y++)
	{

		for(unsigned int x=0; x<width; x++)
		{

			// first check north, east, west and south
			// then we just need to check if it's in one of the four corners
			// it's simple, if the point isn't in one of n,e,w,s than it must be in one of the others
			// and there are only 4 of them and every one in a separate corner ...
			if(inRegionN(x,y))
			{
				mem[x+(y*width)] = LOC_NORTH;

			}else if(inRegionS(x,y))
			{
				mem[x+(y*width)] = LOC_SOUTH;

			}else if(inRegionW(x,y))
			{
				mem[x+(y*width)] = LOC_WEST;

			}else if(inRegionE(x,y))
			{
				mem[x+(y*width)] = LOC_EAST;

			}else if(inRegionSW(x,y))
			{
				mem[x+(y*width)] = LOC_SOUTHWEST;

			}else if(inRegionNE(x,y))
			{
				mem[x+(y*width)] = LOC_NORTHEAST;

			}else if(inRegionNW(x,y))
			{
				mem[x+(y*width)] = LOC_NORTHWEST;

			}else if(inRegionSE(x,y))
			{
				mem[x+(y*width)] = LOC_SOUTHEAST;
			}
			

		}
	
	}

	// create the mapping for the mpeg RoSE

	// for now it's enough to have the ANYWHERE with the height

	// north
	mapping.insert(std::make_pair(LOC_NORTH, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK));

	// northwest
	mapping.insert(std::make_pair(LOC_NORTHWEST, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK));

	// northeast
	mapping.insert(std::make_pair(LOC_NORTHEAST, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK));

	// west
	mapping.insert(std::make_pair(LOC_WEST, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY));

	// east
	mapping.insert(std::make_pair(LOC_EAST, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY));

	// southwest
	mapping.insert(std::make_pair(LOC_SOUTHWEST, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT));

	// southeast
	mapping.insert(std::make_pair(LOC_SOUTHEAST, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT));

	// south
	mapping.insert(std::make_pair(LOC_SOUTH, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT));

	// center
	mapping.insert(std::make_pair(LOC_CENTER, Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY));

	reset();

}

ScreenSplitter::~ScreenSplitter(void)
{
	free(mem);
}

void ScreenSplitter::reset()
{
	
	for(unsigned int i=0; i<DEFINED_LOCATIONS;i++)
	{
		container[i][0] = 0;
		container[i][1] = 0;
		container[i][2] = 0;
		container[i][3] = 0;
		container[i][4] = 0;
	}

}

void ScreenSplitter::insert(unsigned int x, unsigned int y, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4)
{
	if(x > (width-1) || y > (height-1)) return;
	// try to find the location
	container[mem[x+(y*width)]][0] += c1;
	container[mem[x+(y*width)]][1] += c2;
	container[mem[x+(y*width)]][2] += c3;
	container[mem[x+(y*width)]][3] += c4;
	container[mem[x+(y*width)]][4]++;		// that's the pixel count, for average color calculation
//	std::cout << getMapping(mem[x+(y*width)]) << " " << (int)mem[x+(y*width)] << std::endl;
}

void ScreenSplitter::insert(unsigned int x, unsigned int y, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4, unsigned int count)
{
	if(x > (width-1) || y > (height-1)) return;
//	std::cout << c1 << " " << c2 << " " << c3 << std::endl;
	// try to find the location
	container[mem[x+(y*width)]][0] += c1;
	container[mem[x+(y*width)]][1] += c2;
	container[mem[x+(y*width)]][2] += c3;
	container[mem[x+(y*width)]][3] += c4;
	container[mem[x+(y*width)]][4] +=count;		// that's the pixel count, for average color calculation
		
}

unsigned int ScreenSplitter::getLocation(unsigned int x, unsigned int y)
{
	return mem[x+(y*width)];
}

unsigned int ScreenSplitter::getEnumLocations()
{
	return DEFINED_LOCATIONS;
}

void ScreenSplitter::insertAtLocation(unsigned int location, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4, unsigned int count)
{

	container[location][0] += c1;
	container[location][1] += c2;
	container[location][2] += c3;
	container[location][3] += c4;
	container[location][4] += count;	
}

void ScreenSplitter::insertAtLocation(unsigned int location, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int count)
{

	container[location][0] += c1;
	container[location][1] += c2;
	container[location][2] += c3;
	container[location][3] += 0;
	container[location][4] +=count;	
}

unsigned int ScreenSplitter::getLocationComponent(unsigned int comp, unsigned char LOCATION)
{
	if(comp > MAX_COMPONENTS-1) return 0;
	if(container[LOCATION][4] == 0) return 0;
	
	if(container[LOCATION][3] != 0)
	{
		// we have to consider the alpha value
		float alpha = (container[LOCATION][3] / container[LOCATION][4]) / 255.0f;
		
		return (unsigned int)((container[LOCATION][comp] / container[LOCATION][4]) * alpha);

	}

	return container[LOCATION][comp] / container[LOCATION][4];
}

std::string ScreenSplitter::getMapping(unsigned char LOCATION)
{
	std::map<unsigned char,std::string>::iterator it = mapping.find(LOCATION);

	if(it == mapping.end()) return std::string();
	else
		return (*it).second;
}

bool ScreenSplitter::inRegionNAndS(straight &_g1, straight& _g2, unsigned int x, unsigned int y, bool swap)
{

	double n = _g1.m * x + _g1.n;
	double m = _g2.m * x + _g2.n;

	if(!swap)
	{
		if(y <= n && y <= m) return true; 
		return false;
	}else{
		if(y >= n && y >= m) return true;
		return false;
	}
}

bool ScreenSplitter::inRegionWAndE(straight &_g1, straight & _g2, unsigned int x, unsigned int y, bool swap)
{

	double n = _g1.m * x + _g1.n;
	double m = _g2.m * x + _g2.n;

	if(!swap)
	{
		if(y >= n && y <= m) return true; 
		return false;
	}else{
		if(y <= n && y >= m) return true;
		return false;
	}
}

bool ScreenSplitter::inRegionN(unsigned int x, unsigned int y)
{
	if(x < p1.x || x > p2.x || y > my) return false; // the point can't be for sure in this region

	// if so make a more detailed check
	return inRegionNAndS(g1,g2,x,y,false);

}

bool ScreenSplitter::inRegionNW(unsigned int x, unsigned int y)
{

	if(x > mx || y > my) return false;
	return true;

}

bool ScreenSplitter::inRegionW(unsigned int x, unsigned int y)
{
	if(x > mx || y < p3.y || y > p4.y) return false;
	return inRegionWAndE(g3,g4,x,y,false);
}

bool ScreenSplitter::inRegionSW(unsigned int x, unsigned int y)
{
	if(x > mx || y < my) return false;
	return true;
}

bool ScreenSplitter::inRegionS(unsigned int x, unsigned int y)
{
	if(x < p1.x || x > p2.x || y < my) return false;
	return inRegionNAndS(g1,g2,x,y,true);
}

bool ScreenSplitter::inRegionSE(unsigned int x, unsigned int y)
{
	if(x < mx || y < my) return false;
	return true;
}

bool ScreenSplitter::inRegionE(unsigned int x, unsigned int y)
{
	if(x < mx || y < p3.y || y > p4.y) return false;
	return inRegionWAndE(g3,g4,x,y,true);
}

bool ScreenSplitter::inRegionNE(unsigned int x, unsigned int y)
{
	if(x < mx || y > my) return false;
	return true;
}

