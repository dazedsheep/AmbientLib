-----------------------------------------------
06.04.2011 (Benjamin Rainer)
-----------------------------------------------

1. INSTALLATION:
----------------------------------------

  Download the ambientPackage-dev, if you want to write device drivers or help us with the development of AmbientLib, and install it.
  If you just want to use the AmbientLib within your program than just download ambientPackage-lib and install it.
  
2. Using AmbientLib within your program:
----------------------------------------

  Note: AmbientLib is fully written in C/C++, if you are going to use any other language then you may have to write a wrapper, like for java.
  
  First let us talk about how you have to instantiate the library:

  Include the AmbientLib.h header file. There you'll find the exported class which is the interface to the library (I'll call it interface from now on).

  It's rather easy to get the library working with your program just follow these steps:

  Let us get an instance with:

  Ambient *ambientLib = new Ambient(Threads[true/false], fadeTime[true/false], width[of your video frame], height[of your video frame]);

  Now the library intializes everything you need, like the automatic color calculation and so on.

  Ok now it's time to do some magic with the library.

  First we want to set the calculation rate, better said the accuracy of the automatic color calculation.

  ambientLib->setCAcalculationRate(0[pixeljump],0[rowjump]); FYI: PixelJump is defined as follows: This states how many pixels are skipped after every calculated pixel. RowJump, states how many rows are skipped.

  Let us try to calculate some colors out of a video frame.

  For instance unsigned char *frame points to a video frame with 800x600 with an color format of RGBA.

  ambientLib->lightFromPicture(800[width],600[height],frame,IMAGE_FORMAT_RGBA);

  What happens in the background of this function ?

	- The first thing the library will do, it'll calculate the average color for every location (N,S,....).
	- Then it will forward this colors to an appropriate device driver (like amBX).
	- The device driver is then responsible for displaying the colors. 
  
  After you are done using the Ambient Library just delete your instance.
 
  delete ambientLib;

3. Using other effects than the lights (SEM):
---------------------------------------------

  Ok, now you know how you can use the light color calculation and how it works we'll focus on how you can enhance the experience of your app/program with sensory effect descriptions.

  Please see the MPEG-V on how you can create a standard conform SE description. Or use the annotation tool within the package you have installed.

  If you are familiar with MPEG-V or if you have created an SEM file with the annotation tool the next step is making use of the created description.

  For instance the SEM file is located on your harddisk then you will just have to call one function and this will do the magic for you.

  Note: Sometimes it's better to load the SEM before you are starting autmatic color calculation, because there may be also some color descriptions within the SEM file.

  ambientLib->loadSEMFromDisk(path to the SEM file);
  
  This will load the SEM from disk and will send the parsed! sensory effect description to the device drivers

  Every device gets all descriptions, the point is that the device driver should only interpret description which are appropriate for the device.

  After you have loaded the SEM file you can play effects at a given timestamp.

  ambientLib->playEffectAtTimeAbs(time[in seconds.ms...(double)]); Time should be absolute.
  ambientLib->playEffectAtTimeRel(time[in seconds.ms...(double)]); Time should be relative.

  You may now wonder why you can't trigger effects withoug timing, this library was created mainly for videos BUT with a little trick you may be able to trigger effects.

  How to trigger effects if you haven't got timing information ?

  Create an SEM which declares all the effects you want to use. Assign a timestamp to every effect. Now you are able to trigger effects by the defined timestamp(s).  

  --

  If you have an HTTP server and want to store and load SEM files from there, the library gives you the option to retrieve SEM files via HTTP.

  ambientLib->loadSEMHTTP(url[like http://localhost/mySEMS/], semfile[the name of the SEM file], directoryLookup[true/false]);

  If you set directory look up to true then the library expects that the handed over SEM file name is just a part of an SEM file name. 

  It'll retreive a file list from the given url and will search for the given SEM file name. If there are more files it will pick the first one.

  The file is then downloaded via HTTP (ver 1.1) and stored in the local memory and will be parsed afterwards.

  If you want to know if automatic color calculation is on, just use the isAutoColor function to determine it.

  ambientLib->isAutoColor(); ...


4. Which image formats are supported ?
--------------------------------------

  IMAGE_FORMAT_RGB	
  IMAGE_FORMAT_RGBA	
  IMAGE_FORMAT_ARGB	
  IMAGE_FORMAT_BGR
  IMAGE_FORMAT_BGRA
  
5. How can I develop device drivers for the library ?
-----------------------------------------------------

  Please see the HOWTO develop device drivers.
  


  

