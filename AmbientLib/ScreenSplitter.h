/*
 * ScreenSPlitter.h
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

#ifndef SCREEN_SPLITTER_H_
#define SCREEN_SPLITTER_H_

namespace AmbientLib {

#define WIDTH_SPLITTING		((float)1/6)
#define HEIGHT_SPLITTING	((float)1/5)
#define NS_PIECES			(4)
#define WE_PIECES			(3)
#define NWNESWSE_PIECES		(1)

#define LOC_CENTER			0	//NYI
#define LOC_NORTH			1
#define LOC_NORTHWEST		2
#define LOC_NORTHEAST		3
#define LOC_WEST			4
#define LOC_EAST			5
#define LOC_SOUTHWEST		6
#define LOC_SOUTHEAST		7
#define LOC_SOUTH			8

#define DEFINED_LOCATIONS	9
#define MAX_COMPONENTS		4
typedef struct {

	double x;
	double y;

}point;


typedef struct {

	point p;
	double m;
	double n;
}straight;

class ScreenSplitter
{
private:
	unsigned int width, height;
	double mx,my;
	point p1,p2,p3,p4;
	straight g1,g2,g3,g4;
	unsigned char *mem;
	std::map<unsigned char, std::string> mapping;		// provide a mapping between mpeg V standard and our classification
	
	unsigned int container[DEFINED_LOCATIONS][5];

public:
	ScreenSplitter(unsigned int width, unsigned int height);
	~ScreenSplitter(void);
	bool inRegionN(unsigned int x, unsigned int y);
	bool inRegionNW(unsigned int x, unsigned int y);
	bool inRegionW(unsigned int x, unsigned int y);
	bool inRegionSW(unsigned int x, unsigned int y);
	bool inRegionS(unsigned int x, unsigned int y);
	bool inRegionSE(unsigned int x, unsigned int y);
	bool inRegionE(unsigned int x, unsigned int y);
	bool inRegionNE(unsigned int x, unsigned int y);

	bool inRegionNAndS(straight &_g1, straight &_g2, unsigned int x, unsigned int y, bool swap);
	bool inRegionWAndE(straight &_g1, straight &_g2, unsigned int x, unsigned int y, bool swap);
	
	void insert(unsigned int x, unsigned int y, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4);
	void insert(unsigned int x, unsigned int y, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4, unsigned int count);
	
	void insertAtLocation(unsigned int location, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4, unsigned int count);
	void insertAtLocation(unsigned int location, unsigned int c1, unsigned int c2, unsigned int c3, unsigned int count);
	std::string getMapping(unsigned char LOCATION);
	unsigned int getLocationComponent(unsigned int comp, unsigned char LOCATION);
	unsigned int getLocation(unsigned int x, unsigned int y);
	unsigned int getEnumLocations();
	void reset();

};

}

#endif