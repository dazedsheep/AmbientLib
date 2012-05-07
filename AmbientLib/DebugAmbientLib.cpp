/*
 * DebugAmbientLib.cpp
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
#include <vector>

#include "PreReader.h"
#include "Libxml.h"
#include "ptr.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "HTTPConnector.h"
#include "SEMhttp.h"
#include "AmbientLib.h"
#include "DebugAmbientLib.h"
#include "DeviceInterface.h"
#include "DeviceContext.h"
#include "ScreenSplitter.h"
#include "workerPool.h"
#include "colorAlgorithm.h"
#include "limitedFunction.h"
#include "clusteringCalculation.h"


using namespace AmbientLib;

DebugAmbient::DebugAmbient(bool allowThreads,bool disableFateTime, bool enableAutoColor,  unsigned int width, unsigned int height) : Ambient(allowThreads,disableFateTime, enableAutoColor, width, height)
{

}

DebugAmbient::~DebugAmbient(void)
{
	
}

void DebugAmbient::runEffectAnalysis(const char *path,unsigned int length)
{
	clusteringCalculation *calc = new clusteringCalculation(path,length);
	calc->printWindFunction();
	delete calc;
}

bool DebugAmbient::forceColorAlgorithmCPUSupport(bool set)
{

	ptr<colorAlgorithm> p(this->cA);
	return p->forceCPUSupport(set);

}

bool DebugAmbient::colorAlgorithmHasCPUSupport()
{
	ptr<colorAlgorithm> p(this->cA);

	return 	p->haveCPUSupport();
}

bool DebugAmbient::colorAlgorithmUsesCPUSupport()
{
	ptr<colorAlgorithm> p(this->cA);

	return 	p->usingCPUSupport();
}

void DebugAmbient::testHTTP(){
	SEMhttp *semh = new SEMhttp("http://localhost/master/","action");
	
	
	Libxml *xml = new Libxml();

	std::vector<Element *> myElements = xml->parse(semh->fetchFirstSEM(semh->loadSEMList()));

	std::cout << "Parsed elements: " << myElements.size() << std::endl;

	std::cout << "handing effects to device drivers..." << std::endl;
	ptr<DeviceContext> dc(myDC);

	dc->AddEffectsToDevices(myElements);

	delete xml;
	delete semh;

}
static int dummyFunc(void *params, workerParam *wParam)
{
	std::cout << " I AM A DUMMY, called from worker:"<<wParam->threadID << std::endl;
	return 0;
}
void DebugAmbient::testDeviceContextCreate(){

	scoped_ptr<workerPool> wP(new workerPool());
	
	wP->attachAndWait(dummyFunc,NULL);



}

void DebugAmbient::testDeviceContextClose(){

	

	

}


void DebugAmbient::testScreenSplitter(unsigned int x, unsigned int y)
{
	
}




