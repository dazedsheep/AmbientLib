AmbientLib
==========

Library for enriching multimedia/applications with sensory effects (e.g., ambient lights, vibration, wind). It uses the MPEG-V standard. The project includes a Web browser plug-in that uses the AmbientLib. The browser plug-in allows to enrich Web videos by means of sensory effects.

NOTE:
 
Currently only Windows Vista or higher is supported. Linux/Unix/Mac OS support will be added in future releases.

INSTALL:

Before building the package, make sure that you have installed CMake.

run build with the Visual Studio 2010 Command Prompt - This will build the AmbientLib, the Web browser plug-in and a sample device driver. Furthermore, a .msi will be created for installing

After installing the AmbientLib package run postInstall.exe (located in the directory where AmbientLib was installed) as Administrator. This will register the Web browser plug-in and will create the needed registry entries.
