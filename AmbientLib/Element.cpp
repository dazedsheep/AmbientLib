/*
 * Element.cpp
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

#include "stdafx.h"
#include "Element.h"

Element::Element() 
{
	l_time = -1.0;
	i_type = 0;
	played_time = -1.0f;
}

Element::~Element()
{

}

void Element::setPlayedTime(double time)
{
	played_time = time;
}

double Element::getPlayedTime()
{
	return played_time;
}

std::string Element::getValue(std::string identifier)
{
	std::map<std::string, std::string>::const_iterator foundElement;

	foundElement = m_value.find(identifier);
	if (foundElement != m_value.end())
		return foundElement->second;
	else
		return "";
}

std::map<std::string, std::string> Element::getValues()
{
	return m_value;
}

void Element::addValue(std::string identifier, std::string value)
{
	m_value[identifier] = value;
}

double Element::getTime() const
{
	return l_time;
}

void Element::setTime(double time)
{
	l_time = time;
}

void Element::setType(int type)
{
	i_type = type;
}

int Element::getType()
{
	return i_type;
}

void Element::print()
{
	printf("type: %i\ntime: %f\n", i_type, l_time);
	for (std::map<std::string, std::string>::const_iterator it = m_value.begin(); it != m_value.end(); ++it)
		std::cout << it->first << ":" << it->second << ";  ";

	std::cout << std::endl;
}

