// AmbientLibTest.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include <Windows.h>
#include <Mmsystem.h>

#include "..\..\AmbientLib\AmbientLib.h"
#include "..\..\AmbientLib\DebugAmbientLib.h"

using namespace std;


LARGE_INTEGER timerFreq_;
LARGE_INTEGER counterAtStart_;

void startTime()
{
  QueryPerformanceFrequency(&timerFreq_);
  QueryPerformanceCounter(&counterAtStart_);
  cout<<"timerFreq_ = "<<timerFreq_.QuadPart<<endl;
  cout<<"counterAtStart_ = "<<counterAtStart_.QuadPart<<endl;
  TIMECAPS ptc;
  UINT cbtc = 8;
  MMRESULT result = timeGetDevCaps(&ptc, cbtc);
  if (result == TIMERR_NOERROR)
  {
    cout<<"Minimum resolution = "<<ptc.wPeriodMin<<endl;
    cout<<"Maximum resolution = "<<ptc.wPeriodMax<<endl;
  }
  else
  {
    cout<<"result = TIMER ERROR"<<endl;
  }
}
unsigned int calculateElapsedTime()
{
  if (timerFreq_.QuadPart == 0)
  {
    return -1;
  }
  else
  {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    return static_cast<unsigned int>( (c.QuadPart - counterAtStart_.QuadPart) * 1000000 / timerFreq_.QuadPart );
  }
}


void runPerformanceTest(int width,int height,bool useThreads,Ambient *ambientLib){
	int runs = 100;
	unsigned int calculated=0;
	unsigned char *pxData = (unsigned char *) malloc(width*height*4);	//test array
	
	cout << "preparing pixel data...";

	for(int i=0;i<width*height*4;i+=4){
		pxData[i] =255;
		pxData[i+1] = 255;
		pxData[i+2] = 255;
		pxData[i+3] = 255;
	}
	cout << "done." << endl;

	

	// test if our libraray does what we want
	cout << " isAutoColor: "<< ambientLib->isAutoColor() << endl;

	ambientLib->setCACalculationRate(0,0);
	cout << "running color calculation "<<runs<<" times on "<< width <<"x"<<height<< endl;
	unsigned int ams,ems;
	unsigned long avg=0;
	int ret_val;
	while(!kbhit())
	{
		ams = timeGetTime();
		ret_val =  ambientLib->lightFromPicture(pxData,IMAGE_FORMAT_RGBA);
		if(useThreads && ret_val == 5) calculated++;
		ems = timeGetTime();
		avg += ems-ams;

	//	cout << "return value: " << ret_val << endl;
	}

	
	cout << "whole execution time: "<< avg << "ms" << endl;
	if(useThreads){
		cout <<"calculations done: "<<calculated<<endl;
		cout << "average execution time of one call: " << avg/calculated << "ms" << endl;
	}else{
		cout << "average execution time of one call: " << avg/runs << "ms" << endl;
	}
	
	free(pxData);

}


void runEffectTest(bool useThreads,bool disableFateTime,bool usePreReader){

		//DebugAmbient *ambientLib = new DebugAmbient(useThreads,disableFateTime,150,75);
		
		// check the error message of the device context
		//cout << ambientLib->getDeviceErrorMessage() << endl;
		
	//	ambientLib->testScreenSplitter(0,0);


		/*ambientLib->loadSEMFromDisk("test.xml");

		if(ambientLib->isAutoColor())ambientLib->setCACalculationRate(0,0);
		unsigned long timeScale = ambientLib->getTimeScale();
		double time = 0;
		cout << "Time scale of SEM: " << timeScale << endl;
		
		cout << "Trying to play some effects...(30ms updates, 100 seconds)" << endl;
		bool r = false;
		cout << "isAutoColor: " << (ambientLib->isAutoColor() ? "true" : "false") << endl;

		for(int i=0;i<10000/30;i++)
		{
			

			r = ambientLib->playEffectAtTimeAbs(time/timeScale);
			if(r){

				cout << "Played effect at time: " << (float)(time / timeScale) << "s" << endl;

			}

			time += timeScale;
			
		}*/

//		delete ambientLib;


}

void runDebugTests(){

	DebugAmbient *ambientLib = new DebugAmbient(true,false,false,150,75);
	
//	cout << "CPU supports needed features: " << (ambientLib->colorAlgorithmHasCPUSupport() ? "Yes" : "No") << endl;

//	cout << "Lib uses cpu support: " << (ambientLib->colorAlgorithmUsesCPUSupport() ? "Yes" : "No") << endl;

//	cout << "Forcing not to use CPU features: " << (ambientLib->forceColorAlgorithmCPUSupport(false) ? "Done" : "Not allowed") << endl;

//	cout << "Lib uses cpu support: " << (ambientLib->colorAlgorithmUsesCPUSupport() ? "Yes" : "No") << endl;

	ambientLib->loadSEMHTTP("https://localhost/livelab/SEMs/","Iron Man 2 Trailer OFFICIAL.xml", false);

	unsigned long timeScale = ambientLib->getTimeScale();
	double time = 0;
	cout << "Effects loaded: " << (ambientLib->isEffectsLoaded() ? "Yes" : "No") << endl;


	cout << "Time scale of SEM: " << timeScale << endl;
		
	cout << "Trying to play some effects...(30ms updates, 100 seconds)" << endl;
	bool r = false;
	cout << "isAutoColor: " << (ambientLib->isAutoColor() ? "true" : "false") << endl;
	unsigned int ams,ems;
	unsigned long avg=0;
	unsigned int calculated=0;
	float _time = 0.0f;
	while(!kbhit())
	{
		if(_time >= 25.0f) _time = 0.0f;
		else
			_time +=0.1f;
		ams = timeGetTime();
		r = ambientLib->playEffectAtTimeAbs(_time);
		ems = timeGetTime();
		avg += ems-ams;
		calculated++;
	}
	cout << "calcs done: " << calculated << std::endl;
	cout << "average execution time: " << avg/calculated << std::endl;

	delete ambientLib;
	

}

void runEffectDownloadTests(){

	DebugAmbient *ambientLib = new DebugAmbient(true,false,false,150,75);


	ambientLib->loadSEMHTTP("https://demo-itec.uni-klu.ac.at/livelab/content/SEMs/","2009 108 Way World Record Freefly Jump HD.xml", false);

	unsigned long timeScale = ambientLib->getTimeScale();
	double time = 0;
	cout << "Effects loaded: " << (ambientLib->isEffectsLoaded() ? "Yes" : "No") << endl;


	cout << "Time scale of SEM: " << timeScale << endl;
		
	cout << "isAutoColor: " << (ambientLib->isAutoColor() ? "true" : "false") << endl;
	while(!kbhit());
	delete ambientLib;

}

void doEffectAnalysis(const char *sem, const char *length){

	DebugAmbient *ambientLib = new DebugAmbient(true,false,false,150,75);


	ambientLib->runEffectAnalysis(sem,atoi(length));
	
	delete ambientLib;


}

void runFullPerformanceTest(unsigned int _runs)
{

	// The performance test will do perfomance test on the color calculation, without MMX / with MMX, without threading / with threading and on different resolutions
	DebugAmbient *ambientLib;
	unsigned int width,height,bpps,bms,ems,diff,runs=_runs,sleepTime=5000;
	unsigned int i=0;
	unsigned char *vFrame;
	// start at 320x240, 640x360, 1280x720, 1920x1080

	std::cout << "Running tests with Settings: MMX disabled, Threading disabled and pixel format R8G8B8A8" << std::endl;
	timeBeginPeriod(1000000);

	startTime();
	width = 320;
	height = 240;
	bpps = 4;
		
	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 640;
	height = 480;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1280;
	height = 720;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1920;
	height = 1080;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 7680;
	height = 4320;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;

 //----------- ENABLE MMX

	std::cout << std::endl;

	std::cout << "MMX ENABLED" << std::endl;

	width = 320;
	height = 240;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 640;
	height = 480;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1280;
	height = 720;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1920;
	height = 1080;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 7680;
	height = 4320;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(false,false,true,width,height);
	diff=0;
	for(i=0;i<runs;i++)
	{
		bms = calculateElapsedTime();
		ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
		ems = calculateElapsedTime();
		diff += (ems-bms);
	}
	std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	std::cout<<std::endl;
	std::cout << "MMX disabled, Threading enabled" << std::endl;
	std::cout<<std::endl;

	width = 320;
	height = 240;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 640;
	height = 480;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1280;
	height = 720;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1920;
	height = 1080;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 7680;
	height = 4320;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	ambientLib->forceColorAlgorithmCPUSupport(false);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);
	std::cout<<std::endl;
	std::cout << "MMX enabled, Threading enabled" << std::endl;
	std::cout<<std::endl;
	width = 320;
	height = 240;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 640;
	height = 480;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1280;
	height = 720;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 1920;
	height = 1080;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);

	width = 7680;
	height = 4320;
	bpps = 4;

	vFrame = (unsigned char *) malloc(width * height * bpps);
	ZeroMemory(vFrame,width*height*bpps);
	ambientLib = new DebugAmbient(true,false,true,width,height);
	diff=0;
	std::cout << width<<"x"<<height<<": "<<std::endl;
	bms = calculateElapsedTime();
	ambientLib->lightFromPicture(vFrame, IMAGE_FORMAT_RGBA);
	ems = calculateElapsedTime();
	diff += (ems-bms);
	Sleep(sleepTime);
	//std::cout << width<<"x"<<height<<": "<< diff/runs << "micros"<<std::endl;
	delete ambientLib;
	free(vFrame);


	timeEndPeriod(1000000);

}


int _tmain(int argc, _TCHAR* argv[])
{
	bool threading = false;
	Ambient *ambientLib;
/*	cout << "Press any key to continue..." << endl;
	while(!kbhit());

	ambientLib = new Ambient(false,false);
	cout << "Running performance tests on color calculations...(without threads)" << endl;

	cout << "Using resolution of 150x75 pixels" << endl;
	runPerformanceTest(150,75,threading,ambientLib);

	cout << "Using resolution of 400x300 pixels" << endl;
	runPerformanceTest(400,300,threading,ambientLib);

	cout << "Using resolution of 800x600 pixels" << endl;
	runPerformanceTest(800,600,threading,ambientLib);

	cout << "Using resolution of 1024x720 pixels" << endl;
	runPerformanceTest(1024,720,threading,ambientLib);

	cout << "Using resolution of 1680x1050 pixels" << endl;
	runPerformanceTest(1680,1050,threading,ambientLib);
	
	cout << "Using resolution of 1920x1080 pixels" << endl;
	runPerformanceTest(1920,1080,threading,ambientLib);

	cout << "Running performance tests on color calculations...(with threads - non blocking calls)" << endl;
	
	delete ambientLib;

	threading = true;
	*/
/*	ambientLib = new Ambient(true,false);
	cout << ambientLib->getDeviceErrorMessage() << endl;
	cout << "Using resolution of 150x75 pixels" << endl;
	runPerformanceTest(150,75,true,ambientLib);
	
	cout << "Using resolution of 400x300 pixels" << endl;
	runPerformanceTest(400,300,threading,ambientLib);

	cout << "Using resolution of 600x800 pixels" << endl;
	runPerformanceTest(600,800,threading,ambientLib);

	cout << "Using resolution of 1024x720 pixels" << endl;
	runPerformanceTest(1024,720,threading,ambientLib);

	cout << "Using resolution of 1680x1050 pixels" << endl;
	runPerformanceTest(1680,1050,threading,ambientLib);
	
	cout << "Using resolution of 1920x1080 pixels" << endl;
	runPerformanceTest(1920,1080,threading,ambientLib);
	
	delete ambientLib;*/
	

/*	ambientLib = new Ambient(true,false,true,1680,1050);
	cout << "Running color test...." << endl;
	runPerformanceTest(1680,1050,true,ambientLib);
	
	delete ambientLib;
	*///cout << "Running effect tests...(without pre reader)" << endl;
	//runEffectTest(true,false,false);
	
//	DebugAmbient *da = new DebugAmbient(true,false,640,480);
//	da->testDeviceContextCreate();
//	delete da;
	//runDebugTests();
//	runEffectDownloadTests();
	doEffectAnalysis(argv[1],argv[2]);
	//runFullPerformanceTest(500);
//	while(!kbhit());
//	runEffectDownloadTests();
	
	return 0;
}

