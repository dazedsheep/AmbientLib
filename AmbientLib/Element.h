/*
 * Element.h
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

#ifndef ELEMENT_H
#define ELEMENT_H

#include <map>
#include <string>
#include <iostream>

class Element
{
private:
	std::map<std::string, std::string> m_value;
	int i_type;
	double l_time;
	double played_time;
public:
	Element();
	~Element();
	std::map<std::string, std::string> getValues();
	std::string getValue(std::string identifier);
	void addValue(std::string identifier, std::string value);
	double getTime() const;
	void setTime(double time);
	void setPlayedTime(double time);
	double getPlayedTime();
	void print();
	void setType(int type);
	int getType();
};

#endif
