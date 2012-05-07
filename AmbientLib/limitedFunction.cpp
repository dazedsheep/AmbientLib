/*
 * limitedFunction.cpp
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
#include <iostream>
#include "limitedFunction.h"


limitedFunction::limitedFunction(double x1, double y1, double x2, double y2, double lowerLimit, double upperLimit)
{
	// calculate the straight
	isConstant = false;


	k = (y2-y1)/(x2-x1);

	// y = k*x+d => d = y-k*x
	d = y1 - k*x1;
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
	this->x1 = x1;
	this->y1 = y1;
}

limitedFunction::limitedFunction(double y, double lowerLimit, double upperLimit)
{
	isConstant = true;
	k = y;
	d=0;
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
}

limitedFunction::~limitedFunction(void)
{
}

double limitedFunction::function(double x)
{
	if(!isConstant && x >= lowerLimit && x <= upperLimit) return k*x+d;
	if(isConstant && x >= lowerLimit && x <= upperLimit) return k;

	// otherwise not defined or -1 ... undef doesn't exist in doubles ... maybe ...
	// mathematical correct will be returning nothing or throwing an exception ... but ...
	return -1;
}

double limitedFunction::getLowerLimit() { return lowerLimit; }

double limitedFunction::getUpperLimit() { return upperLimit; }

double limitedFunction::getK()	{ return k; }

void limitedFunction::recalc(double x2, double y2, double lowerLimit, double upperLimit)
{
isConstant = false;


	k = (y2-y1)/(x2-x1);

	// y = k*x+d => d = y-k*x
	d = y1 - k*x1;
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
}

double limitedFunction::getFunctionArea()
{
	// calculate the are below our function

	// for constants it's easy
	if(isConstant)
	{
		//std::cout << " " << k*(upperLimit - lowerLimit);
		return k*(upperLimit - lowerLimit);		

	}else{
		// we have to make use of the integration to calculate the area below this partial function
		// since we have only straights we can calculate the area with a triangle + a rectangle
		double y1,y2,a,b,Ft;
		if( k < 0)
		{
			y1 = k*lowerLimit + d;
			y2 = k*upperLimit + d;
		}else{
			y2 = k*lowerLimit + d;
			y1 = k*upperLimit + d;
		}
		
		b=y1-y2;
		a = upperLimit - lowerLimit;
		Ft = ((a*b)/2) + (a*y2);
		//std::cout << " " << Ft;
		return Ft;
	}

}

double limitedFunction::getVariation()
{

	if(!isConstant) return abs((k*upperLimit+d) - (k*lowerLimit+d));

	// for constants the problem is that we have to know the y before this function and afterwards

}

bool limitedFunction::constant()
{
	return isConstant;
}

void limitedFunction::print()
{

	if(isConstant)
	{

		std::cout << k << " limits:" << lowerLimit << "<= x <" << upperLimit << std::endl;

	}else{
		std::cout << k << "*x" << (d > 0 ? "+" : "") << d << " limits:" << lowerLimit << "<= x <" << upperLimit << std::endl;
	}

}