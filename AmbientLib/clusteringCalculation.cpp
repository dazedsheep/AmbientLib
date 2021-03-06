/*
 * clusteringCalculation.cpp
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universitšt Klagenfurt
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
#include <vector>

#include "Element.h"
#include "PreReader.h"
#include "Libxml.h"
#include "ptr.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "HTTPConnector.h"
#include "SEMhttp.h"
#include "AmbientLib.h"
#include "limitedFunction.h"
#include "clusteringCalculation.h"
#include "typedef.h"



clusteringCalculation::clusteringCalculation(const char *SEMFile_path,unsigned int length)
{

	ptr<Libxml> xml(new Libxml());
	std::vector<Element *>::iterator it;
	elements =	xml->parse(SEMFile_path);
	this->length = length;
	if(elements.size() > 0)
	{
		bool w_enabled = false,w_fade=false;
		double woldi=0,wnewi=0,woldpts=0,wnewpts=0,wfadetime=0;
		bool v_enabled = false,v_fade=false;
		double voldi=0,vnewi=0,voldpts=0,vnewpts=0,vfadetime=0;
		
		// begin to calculate the overall function
		for(it=elements.begin(); it != elements.end(); ++it)
		{

			switch((*it)->getType())
			{
			case TYPE_FAN:
				// our wind

				
				if(strcmp((*it)->getValue(ATT_GEN_ACTIVATE).c_str(),SEMP_TRUE)==0)
				{
				
					if(atof((*it)->getValue(ATT_GEN_FADE).c_str()) > 0)
					{
						// we have a fade effect

						wfadetime = atof((*it)->getValue(ATT_GEN_FADE).c_str());
						
						// we may have the case that we fade within a wind effect
						if(w_enabled)
						{
							functionWind.push_back(limitedFunction(wnewi,woldpts,(*it)->getTime()));
							woldi=wnewi;
						}
						if(w_fade)
						{
							// if we had a fade before, the fade may be shorter than the whole effect
							if(woldpts < (*it)->getTime())
							{
								functionWind.push_back(limitedFunction(woldi,woldpts,(*it)->getTime()));
							}
						}
						// the old intensity is our starting point
						wnewi = atof((*it)->getValue(ATT_INTENSITYVALUE).c_str())/100.0f;
						wnewpts = (*it)->getTime();
						w_enabled = false;
						functionWind.push_back(limitedFunction(wnewpts,woldi,wnewpts+wfadetime,wnewi,wnewpts,wnewpts+wfadetime));
						// some times the fade is shorter than the effect itself so we have a straigt line after the fade
						woldi = wnewi;
						woldpts =wnewpts + wfadetime;
						w_fade = true;
					
					}else{
						if(w_enabled)
						{
							functionWind.push_back(limitedFunction(wnewi,woldpts,(*it)->getTime()));
						}
						if(w_fade)
						{
							if(woldpts < (*it)->getTime())
							{
								functionWind.push_back(limitedFunction(woldi,woldpts,(*it)->getTime()));
							}

						}
						w_enabled = true;
						woldpts = (*it)->getTime();
						wnewi = 	atof((*it)->getValue(ATT_INTENSITYVALUE).c_str())/100.0f;					
						w_fade = false;
					}
					
				}

				if(strcmp((*it)->getValue(ATT_GEN_ACTIVATE).c_str(),SEMP_FALSE)==0 && w_fade)
				{
					// this is the end of our wind effect
					w_enabled=false;
					if(woldpts < (*it)->getTime())
					{
								functionWind.push_back(limitedFunction(woldi,woldpts,(*it)->getTime()));
					}
					woldi = wnewi;
					w_fade = false;
				}


				if(strcmp((*it)->getValue(ATT_GEN_ACTIVATE).c_str(),SEMP_FALSE)==0 && w_enabled)
				{
					// this is the end of our wind effect
					w_enabled=false;
					wnewpts = (*it)->getTime();
					functionWind.push_back(limitedFunction(wnewi,woldpts,wnewpts));
					woldpts = wnewpts;
					woldi = 0;
					w_fade = false;
				}

				
				break;

			case TYPE_VIBRATOR:
				// the same for vibration
				if(strcmp((*it)->getValue(ATT_GEN_ACTIVATE).c_str(),SEMP_TRUE)==0)
				{
				
					if(atof((*it)->getValue(ATT_GEN_FADE).c_str()) > 0)
					{
						// we have a fade effect

						vfadetime = atof((*it)->getValue(ATT_GEN_FADE).c_str());
						
						// we may have the case that we fade within a wind effect
						if(v_enabled)
						{
							functionVibration.push_back(limitedFunction(vnewi,voldpts,(*it)->getTime()));
							voldi=vnewi;
						}
						if(v_fade)
						{
							// if we had a fade before, the fade may be shorter than the whole effect
							if(voldpts < (*it)->getTime())
							{
								functionVibration.push_back(limitedFunction(voldi,voldpts,(*it)->getTime()));
							}
						}
						// the old intensity is our starting point
						vnewi = atof((*it)->getValue(ATT_INTENSITYVALUE).c_str())/100.0f;
						vnewpts = (*it)->getTime();
						v_enabled = false;
						functionVibration.push_back(limitedFunction(vnewpts,voldi,vnewpts+vfadetime,vnewi,vnewpts,vnewpts+vfadetime));
						// some times the fade is shorter than the effect itself so we have a straigt line after the fade
						voldi = vnewi;
						voldpts =vnewpts + vfadetime;
						v_fade = true;
					
					}else{
						if(v_enabled)
						{
							functionVibration.push_back(limitedFunction(vnewi,voldpts,(*it)->getTime()));
						}
						if(v_fade)
						{
							if(voldpts < (*it)->getTime())
							{
								functionVibration.push_back(limitedFunction(voldi,voldpts,(*it)->getTime()));
							}

						}
						v_enabled = true;
						voldpts = (*it)->getTime();
						vnewi = atof((*it)->getValue(ATT_INTENSITYVALUE).c_str())/100.0f;					
						v_fade = false;
					}
					
				}

				if(strcmp((*it)->getValue(ATT_GEN_ACTIVATE).c_str(),SEMP_FALSE)==0 && v_fade)
				{
					// this is the end of our wind effect
					v_enabled=false;
					if(voldpts < (*it)->getTime())
					{
						functionVibration.push_back(limitedFunction(voldi,voldpts,(*it)->getTime()));
					}
					voldi = vnewi;
					v_fade = false;
				}


				if(strcmp((*it)->getValue(ATT_GEN_ACTIVATE).c_str(),SEMP_FALSE)==0 && v_enabled)
				{
					// this is the end of our wind effect
					v_enabled=false;
					vnewpts = (*it)->getTime();
					functionVibration.push_back(limitedFunction(vnewi,voldpts,vnewpts));
					voldpts = vnewpts;
					voldi = 0;
					v_fade = false;
				}



				break;

			}
		}
		

	}


}


void clusteringCalculation::printWindFunction()
{
	std::vector<limitedFunction>::iterator it;
	double area=0;

	std::cout << "Wind function:"<<std::endl;

	for(it = functionWind.begin(); it != functionWind.end(); ++it)
	{
		(*it).print();
		area+= (*it).getFunctionArea();
	}
	// the last entry holds the length of the SEM / movie
	
	std::cout << "Average intesity: " << area / length << std::endl; 
	std::cout << "Average change in intensity: " << getVariationOfFunction(functionWind) << std::endl;
	std::cout << "Peak Intensity: " << getPeakIntensity(functionWind)<<std::endl;


	// vibration :)
	std::cout << "Vibration function:"<<std::endl;
	area = 0.0;
	for(it = functionVibration.begin(); it != functionVibration.end(); ++it)
	{
		(*it).print();
		area+= (*it).getFunctionArea();
	}
	// the last entry holds the length of the SEM / movie
	
	std::cout << "Average intesity: " << area / length << std::endl; 
	std::cout << "Average change in intensity: " << getVariationOfFunction(functionVibration) << std::endl;
	std::cout << "Peak Intensity: " << getPeakIntensity(functionVibration)<<std::endl;


}

std::vector<limitedFunction> clusteringCalculation::getWindFunction()
{
	return functionWind;
}

std::vector<limitedFunction> clusteringCalculation::getVibrationFunction()
{
	return functionVibration;
}

double clusteringCalculation::getVariationOfFunction(std::vector<limitedFunction> &function)
{
	// calculate average variation of intensity
	// expect that all undefined parts are 0 so we get a lot of intensity changes througout the video
	std::vector<limitedFunction>::iterator it;
	double llimit=0,lasti=0,_lasti=0;	// start at the beginning of the video, for sake ... 0s :P
	double var=0,cvar=0;
	for(it = function.begin(); it != function.end(); ++it)
	{

		if(llimit == (*it).getLowerLimit())
		{
			// we have no gap in between two effects
			if((*it).constant()) 
			{
			
					_lasti = abs((*it).function((*it).getLowerLimit()));
			//		std::cout << "constant: " << lasti << " " << _lasti << std::endl;
					_lasti = floor((pow(10.0,2)*(_lasti - lasti)+0.5))/pow(10.0,2);
			//		std::cout << "constant step2: " << _lasti << std::endl;
					if(_lasti != 0)
					{
						var += abs(_lasti);
						cvar++;
					}
					lasti = abs((*it).function((*it).getLowerLimit()));
	
			}else
			{
				_lasti = (*it).function((*it).getUpperLimit()) - (*it).function((*it).getLowerLimit());
				var += abs(_lasti);
				cvar++;
				lasti +=_lasti;
			//	std::cout << "fade new i: " << lasti << " " << _lasti << std::endl;
			}
			
			//std::cout << "1.found intensity change: " << llimit << " - " << (*it).getLowerLimit()  << " i: " << _lasti << std::endl;
			llimit = (*it).getUpperLimit();
			
			
			
		}

		if(llimit < (*it).getLowerLimit() && lasti==0)
		{
			// uhm there is a change
			if((*it).constant()) lasti = abs((*it).function((*it).getLowerLimit()));
			else
				lasti = abs((*it).function((*it).getUpperLimit()) - (*it).function((*it).getLowerLimit()));

			var += lasti;
		//	std::cout << "2.found intensity change: " << llimit << " - " << (*it).getLowerLimit()  << " i: " << lasti << std::endl;
			cvar++;
			llimit = (*it).getUpperLimit();
		}

		if(llimit < (*it).getLowerLimit() && lasti>0)
		{
			// there is a 0 part in between these two effects
			
			var += lasti;
			cvar++;
		//	std::cout << "3.found gap change: " << llimit << " - " << (*it).getLowerLimit()  << " i: " << lasti << std::endl;
			// and now the jump from 0 to the current effect intensity
			if((*it).constant()) lasti = abs((*it).function((*it).getLowerLimit()));
			else
				lasti = abs((*it).function((*it).getLowerLimit()) - (*it).function((*it).getUpperLimit()));

			var += lasti;
		//	std::cout << "4.found intensity change: " << llimit << " - " << (*it).getLowerLimit()  << " i: " << lasti << std::endl;
			cvar++;
			llimit = (*it).getUpperLimit();
		}



	}
	
	// if there is no additional effect the last change will be omitted

	// get the last effect and check whether it exceeds the length of the movie or not

	limitedFunction lf = function.at(function.size()-1);

	if(lf.getUpperLimit() < (double)(length) && lf.constant() && lf.function(lf.getLowerLimit()) > 0) 
	{
		var += abs(lf.function(lf.getLowerLimit()));
		cvar++;
	}

	std::cout << "changes: " << cvar << std::endl;

	return var/cvar;

}

double clusteringCalculation::getPeakIntensity(std::vector<limitedFunction> &function)
{
	std::vector<limitedFunction>::iterator it;
	double peakI=0;
	
	for(it = function.begin(); it != function.end(); ++it)
	{
		if((*it).function((*it).getLowerLimit()) > peakI) peakI = (*it).function((*it).getLowerLimit());
		if((*it).function((*it).getUpperLimit()) > peakI) peakI = (*it).function((*it).getUpperLimit());
	}


	return peakI;
}

clusteringCalculation::~clusteringCalculation(void)
{
}
