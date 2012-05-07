/*
 * workerPool.h
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

#ifndef WORKER_POOL_H_
#define WORKER_POLL_H_

namespace AmbientLib 
{

typedef struct workerParam_t{

	HANDLE myHandle;
	unsigned int threadID;		// the number of the thread
	unsigned int workers;		// the number of workers within this worker pool
	HANDLE threadMutex;			// for causing wait situations
	HANDLE threadEvent;			// for signaling that the worker should do it's work
	HANDLE workerIsWorking;		// for signaling that we are working ...
	HANDLE workerFinished;		// event for signaling that the worker is done
	bool running;
	bool synchronized;
	void *threadData;
	(int)(*threadFunc)(void *params, workerParam_t *wParam);


}workerParam;


class workerPool
{
private:
	DWORD *threadIDs;
	unsigned int workers;
	workerParam *wParam;
	HANDLE *threads;
	HANDLE poolMutex;
	HANDLE *threadsReady;
	bool running;
public:
	workerPool(void);
	workerPool(unsigned int workers);
	~workerPool(void);

	static DWORD worker(LPVOID *params);
	int attachAndWait(void *threadFunc,void *params);
	int attach(void *threadFunc, void *params);
};
typedef int (*ThreadFunction)(void *params,workerParam *wParam);
}

#endif