/*
 * colorAlgorithm.h
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

#ifndef _COLORALGORITHM_H_
#define _COLORALGORITHM_H_


#include "threading.h"


namespace AmbientLib{

/*
 * Valid image data formats
 */

#define IMAGE_FORMAT_RGB		0x100
#define IMAGE_FORMAT_RGBA		0x200
#define IMAGE_FORMAT_ARGB		0x300
#define IMAGE_FORMAT_BGR		0x400
#define IMAGE_FORMAT_BGRA		0x500
#define IMAGE_INVALID_FORMAT	0x000

/*
 * Default pixel calculation rates
 * Every N pixel and every N row is used to compute the dominant color
 */

#define DEFAULT_CALCULATION_PIXEL_JUMP	10
#define DEFAULT_CALCULATION_ROW_JUMP 2



class colorAlgorithm;

typedef struct {
	float width;
	float height;
	int format;
	unsigned char *data;
	int pixelJump,rowJump;
	colorAlgorithm *cA;
}threadData;

typedef struct {
	unsigned short *c1;
	unsigned short *c2;
	unsigned short *c3;
	unsigned short *c4;
}components;

class colorAlgorithm {
protected:
	ptr<DeviceContext> DC;
	int pixelJump,rowJump;

private:


	bool allowThreads;
	bool cpuFeaturesSupported,useCPUFeatures;
	int calcRGB(long stride,float height, unsigned char *rawData);
	int calcRGBA(long stride,float height, unsigned char *rawData);
	int calcBGRA(long stride,float height, unsigned char *rawData);
	int calcARGB(long stride,float height, unsigned char *rawData);
	int calcBGR(long stride,float height, unsigned char *rawData);
	int bytesPerFormat(int FORMAT);
	

	// calculations for threads

	int _t_calcRGB(unsigned long stride,unsigned int startHeight, unsigned int endHeight,unsigned int **container, unsigned char *rawData);
	int _t_calcRGBA(unsigned long stride,unsigned int startHeight, unsigned int endHeight,unsigned int **container, unsigned char *rawData);
	int _t_calcBGRA(unsigned long stride,unsigned int startHeight, unsigned int endHeight,unsigned int **container, unsigned char *rawData);
	int _t_calcARGB(unsigned long stride,unsigned int startHeight, unsigned int endHeight,unsigned int **container, unsigned char *rawData);
	int _t_calcBGR(unsigned long stride,unsigned int startHeight, unsigned int endHeight,unsigned int **container, unsigned char *rawData);


public:
	
	threadData tData;
	HANDLE m_ThreadMutex;
	HANDLE m_ScreenSplitterMutex;
	HANDLE m_ThreadEvent;
	HANDLE m_ThreadLocksDone;
	DWORD dwThreadId;
	HANDLE m_Thread;
	ptr<workerPool> wPool;
	ptr<ScreenSplitter> screenSplitter;

	colorAlgorithm(ptr<DeviceContext> dc,ptr<ScreenSplitter> splitter, bool);
	~colorAlgorithm();

	static void threadedCalculation(void *threadD, workerParam *wParam);

	void clearLights();

	void setCalculationRate(int pixelJump, int rowJump);
	
	int calcColor(float width, float height, unsigned char *rawData,int FORMAT);
	int calcColorThreaded(float width, float height, unsigned char *rawData, int FORMAT);
	int doCalculation(float width, float height, unsigned char *rawData, int FORMAT);

	// MMX speed up implementations
	void addThreeComponentDataMMX(unsigned int currentX, unsigned char *rawData,components *cps);
	void addFourComponentDataMMX(unsigned int currentX, unsigned char *rawData,components *cps);

	// standard implementations
	unsigned int addThreeComponentData(unsigned int currentX, unsigned char *rawData);
	unsigned int addFourComponentData(unsigned int currentX, unsigned char *rawData);

	// debugging things, use with CAUTION !
	bool forceCPUSupport(bool mmx);		// returns if the force was an success
	bool haveCPUSupport();
	bool usingCPUSupport();

	void forwardColorToDevice();
	
};

}

#endif _COLORALGORITHM_H_