
/*
 * PreReader.h
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

#ifndef PREREADER_H
#define PREREADER_H

#include <vector>
#include <string>
#include "Element.h"
#include "Classification.h"

class PreReader
{
private:
	Classification classification;
	long m_timeScale;
	Element *m_tmpElement;
	void streamFile(const char *filename);
	std::vector<Element*> *m_Elements;

public:
	PreReader();
	~PreReader();
	std::vector<Element*> parse(const char* filename);
	long getTimeScale();
};

#endif
