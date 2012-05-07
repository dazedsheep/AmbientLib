// postInstall.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <ShTypes.h>
#include <ShellAPI.h>
#include <Windows.h>
#include <stdio.h>
#include <direct.h>
#include <string>
#define GetCurrentDir _getcwd

int _tmain(int argc, _TCHAR* argv[])
{
	ShellExecute(NULL, NULL, "doRegister.cmd", NULL, NULL,  SW_SHOW);

	// get the current directory
	char cDir[FILENAME_MAX];
	GetCurrentDir(cDir, sizeof(cDir) / sizeof(TCHAR));
	HKEY key;
	std::string envPath(cDir);
	// add the slashes to the cDir
	/*for(unsigned int i=0;i<envPath.length();i++)
		{
			if (envPath[i] == '\\'){
				envPath.insert(i,1,'\\');
				i++;
			}
		}
*/
	if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, 0, &key))
	{
		
		if(ERROR_SUCCESS == RegSetKeyValue(HKEY_LOCAL_MACHINE,"System\\CurrentControlSet\\Control\\Session Manager\\Environment", _T("AMBIENT"), REG_SZ, (LPBYTE)envPath.c_str(), envPath.length()))
		{
			::MessageBoxA(NULL,"Environment variable was successfuly set!","AmbientLib post install.", MB_OK);		
			
		}else{

			::MessageBoxA(NULL,"The environment variable could not be set. Please retry running postInstall.exe as admin!", "AmbientLib post install.", MB_OK);
		}
		
		RegCloseKey(key);
	}
	
	char *buf = "Environment";
	int result;
	SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) buf, SMTO_NORMAL, 4000, (PDWORD_PTR) &result);
	printf("wdir: %s \n", cDir);
	
	return 0;
}

