/*
 * PreReader.cpp
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universität Klagenfurt
 *
 * Created on: April 9, 2011
 * Authors: Benjamin Rainer <benjamin.rainer@itec.aau.at>
 *			Markus Waltl	<markus.waltl@itec.aau.at>s
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
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "PreReader.h"
#include "typedef.h"

PreReader::PreReader()
{
	m_Elements = new std::vector<Element*>();
	m_timeScale = 1;
	m_tmpElement = NULL;
}

PreReader::~PreReader()
{
	if (m_Elements != NULL)
	{
		delete m_Elements;
		m_Elements = NULL;
	}
}

std::vector<Element*> PreReader::parse(const char* filename)
{
    streamFile(filename);

    return *m_Elements;
}

void PreReader::streamFile(const char *filename) {

	std::ifstream infile(filename);
	if (!infile.bad())
	{
		char line[1024];
		while(infile.getline(line, 1024))
		{
			char* ch = 0;
			if ((ch = strchr(line, '=')) != NULL)
			{
				int pos = (int)(ch - line);
				std::string tmpString = line;

				std::string domain = tmpString.substr(0, pos);
				std::string range = tmpString.substr(pos+1, tmpString.length());

				if (strcmp(domain.c_str(), "PTS") == 0)
				{
					long int lVal = atol(range.c_str());
					m_timeScale = lVal;
				}
				else
				{
					if (m_tmpElement == NULL)
					{
						m_tmpElement = new Element();
						m_tmpElement->setPlayedTime(-1.0);
					}
					long int lVal = atol(domain.c_str());
					char buffer[1024];
					sprintf_s(buffer, "%.1f", ( lVal / (double)m_timeScale ));
					m_tmpElement->setTime(atof(buffer));
					m_tmpElement->setType(TYPE_LIGHT);
					m_tmpElement->addValue(ATT_GEN_ACTIVATE, SEMP_TRUE);
					m_tmpElement->addValue(ATT_GEN_LOCATION, Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE);
					m_tmpElement->addValue(ATT_LIGHT_COLOR, range.c_str());

					if (m_tmpElement != NULL)
					{
						m_Elements->push_back(m_tmpElement);
						m_tmpElement = NULL;
					}
				}
			}
		}
	}
	else
		fprintf(stderr, "Unable to open %s\n", filename);
}

long PreReader::getTimeScale()
{
	return m_timeScale;
}
