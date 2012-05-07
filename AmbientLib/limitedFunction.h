/*
 * limitedFunction.h
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

#ifndef LIMITEDFUNCTION_H_
#define LIMITEDFUNCTION_H_


class limitedFunction
{
private:
	double k;
	double d;
	bool isConstant;
	double lowerLimit;
	double upperLimit;
	double x1,y1;
public:
	limitedFunction(double x1, double y1, double x2, double y2, double lowerLimit, double upperLimit);
	limitedFunction(double y, double lowerLimit, double upperLimit);
	double function(double x);
	void recalc(double x2, double y2, double lowerLimit, double upperLimit);
	bool constant();
	double getFunctionArea();
	double getVariation();
	void print();
	double getLowerLimit();
	double getUpperLimit();
	double getK();
	~limitedFunction(void);
};

#endif