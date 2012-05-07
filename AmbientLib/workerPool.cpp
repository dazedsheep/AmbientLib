/*
 * workerPool.cpp
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
#include <Windows.h>
#include "ptr.h"
#include "workerPool.h"


using namespace AmbientLib;

workerPool::workerPool(void)
{
	// check how many CPUs / cores we have
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	// create our worker pool
	workers = sysInfo.dwNumberOfProcessors;
	threads = new HANDLE[workers]();
	threadIDs = new DWORD[workers]();
	threadsReady = new HANDLE[workers]();
	
	wParam = (workerParam*) malloc(sizeof(workerParam) * workers);
	memset(wParam, 0, sizeof(workerParam)*workers);
	for(unsigned int i=0;i<workers;i++)
	{
		// create mutex for every thread, events, ...
		wParam[i].threadData = NULL;
		wParam[i].threadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		wParam[i].threadID = i;
		wParam[i].threadMutex = CreateMutex(NULL, FALSE, NULL);
		wParam[i].threadFunc = NULL;
		wParam[i].running = TRUE;
		threads[i] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &worker, &wParam[i],NULL, &threadIDs[i]);
		wParam[i].myHandle = threads[i];
		threadsReady[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		wParam[i].workerFinished = threadsReady[i];
		wParam[i].workers = workers;
	}
	poolMutex = CreateMutex(NULL, FALSE, NULL);
//	::MessageBoxA(NULL,_TEXT("workerpool with max threads..."), _TEXT("wokerpool msg"), MB_OK);
}


workerPool::workerPool(unsigned int workers)
{

	this->workers = workers;
	threads = new HANDLE[workers]();
	threadIDs = new DWORD[workers]();
	threadsReady = new HANDLE[workers]();
	
	wParam = (workerParam*) malloc(sizeof(workerParam) * workers);
	memset(wParam, 0, sizeof(workerParam)*workers);
	for(unsigned int i=0;i<workers;i++)
	{
		// create mutex for every thread, events, ...
		wParam[i].threadData = NULL;
		wParam[i].threadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		wParam[i].threadID = i;
		wParam[i].threadMutex = CreateMutex(NULL, FALSE, NULL);
		wParam[i].threadFunc = NULL;
		wParam[i].running = TRUE;
		threadsReady[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		wParam[i].workerFinished =  threadsReady[i];
		threads[i] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) &worker, &wParam[i],NULL, &threadIDs[i]);
		wParam[i].myHandle = threads[i];
		wParam[i].workers = workers;
	}
	

	poolMutex = CreateMutex(NULL, FALSE, NULL);
//	::MessageBoxA(NULL,_TEXT("workerpool with limited threads..."), _TEXT("wokerpool msg"), MB_OK);
}


DWORD workerPool::worker(LPVOID *params)
{
	workerParam *wParam = (workerParam*) params;

	while(wParam->running)
	{
		
		WaitForSingleObject(wParam->threadEvent,INFINITE);
		ResetEvent(wParam->threadEvent);
		WaitForSingleObject(wParam->threadMutex,INFINITE);
		
		// call our function
		wParam->threadFunc(wParam->threadData,wParam);
		
		ReleaseMutex(wParam->threadMutex);
		if(wParam->synchronized) SetEvent(wParam->workerFinished);
	
	};
	return 0;
}

int workerPool::attachAndWait(void *threadFunc,void *params)
{

	if(threadFunc == NULL) return -1;

	WaitForSingleObject(poolMutex,INFINITE);

	for(unsigned int i=0;i<workers;i++)
	{
		WaitForSingleObject(wParam[i].threadMutex,INFINITE);		// lock thread
		wParam[i].threadData = params;
		wParam[i].synchronized = true;
		wParam[i].threadFunc = (ThreadFunction)threadFunc;
		SetEvent(wParam[i].threadEvent);							// tell him that there is work
		ReleaseMutex(wParam[i].threadMutex);						// unlock thread
	}
	
	// wait on all threads
	WaitForMultipleObjects(workers,threadsReady,true,INFINITE);
	for(unsigned int i=0;i<workers;i++) ResetEvent(threadsReady[i]);

	ReleaseMutex(poolMutex);

	return 0;
}

int workerPool::attach(void *threadFunc, void *params)
{
	if(threadFunc == NULL) return -1;

	WaitForSingleObject(poolMutex,INFINITE);

	for(unsigned int i=0;i<workers;i++)
	{
		WaitForSingleObject(wParam[i].threadMutex,INFINITE);		// lock thread
		wParam[i].threadData = params;
		wParam[i].synchronized = false;
		wParam[i].threadFunc = (ThreadFunction)threadFunc;
		SetEvent(wParam[i].threadEvent);							// tell him that there is work
		ReleaseMutex(wParam[i].threadMutex);						// unlock thread
	}
	
	ReleaseMutex(poolMutex);

	return 0;

}

workerPool::~workerPool(void)
{
	ReleaseMutex(poolMutex);
	CloseHandle(poolMutex);
	
	for(unsigned int i=0;i<workers;i++)
	{
		if(wParam != NULL)
		{
			if(wParam[i].myHandle!=NULL)
			{
				TerminateThread(wParam[i].myHandle,0);
				CloseHandle(wParam[i].myHandle);
			}
			CloseHandle(wParam[i].threadEvent);
			ReleaseMutex(wParam[i].threadMutex);
			CloseHandle(wParam[i].threadMutex);
			CloseHandle(wParam[i].workerFinished);
		}
	}

	free(wParam);
	delete []threadsReady;
	delete []threads;
	delete []threadIDs;

}