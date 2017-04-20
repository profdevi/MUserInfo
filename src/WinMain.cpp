/*    
    MUserInfo.exe : Display access token privledges of the current process
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//v1.0 copyright Comine.com  20170412W1408
#include <Windows.h>
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MMachineInfo.h"
#include "MWinShellInfo.h"
#include "MUserInfo.h"
#include "MBuffer.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MUserInfo";
static const char *GApplicationVersion="1.0";

/////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpCmdLine,int nCmdShow)
	{
	MCommandArg args;
	if(args.Create(lpCmdLine)==false)
		{
		// Unable to construct MCommandArg Object
		return 1;
		}

	MBuffer buffer(4096);
	MBuffer line(2048);

	MStdGetUserName(line.GetBuffer(),line.GetSize()-2);
	buffer.SetString("User Name:\t");
	buffer.StringAppend(line.GetBuffer());
	buffer.StringAppend("\r\n");

	
	MUserInfo userinfo(true);	
	MString str;

	userinfo.GetHomeDir(str);
	buffer.StringAppend("Home Dir:  \t");
	buffer.StringAppend(str.Get() );
	buffer.StringAppend("\r\n");

	
	userinfo.GetDesktopDir(str);
	buffer.StringAppend("Desktop:    \t");
	buffer.StringAppend(str.Get() );
	buffer.StringAppend("\r\n");

	userinfo.GetAllUsersDesktopDir(str);
	buffer.StringAppend("All Desktop: \t");
	buffer.StringAppend(str.Get() );
	buffer.StringAppend("\r\n");

	userinfo.GetLocalAppDataDir(str);
	buffer.StringAppend("Local App Data:\t");
	buffer.StringAppend(str.Get() );
	buffer.StringAppend("\r\n");

	MStdGetMachineName(line.GetBuffer(),line.GetSize()-2);
	buffer.StringAppend("Machine Name:\t");
	buffer.StringAppend(line.GetBuffer());
	buffer.StringAppend("\r\n");

	MMachineInfo machinfo(true);
	buffer.StringAppend("CPU Info:   \t");
	buffer.StringAppend(machinfo.GetCPUInfo() );
	buffer.StringAppend("\r\n");

	buffer.StringAppend("OS Name:   \t");
	buffer.StringAppend(machinfo.GetOSName() );
	buffer.StringAppend("\r\n");

	buffer.StringAppend("Build Number:\t");
	buffer.StringAppend(MStdStr(machinfo.GetBuildNumber()) );
	buffer.StringAppend("\r\n");

	buffer.StringAppend("Version Number:\t");
	MStdSPrintf(line.GetBuffer(),line.GetSize()-2,"%d.%d",machinfo.GetMajorVersion(),machinfo.GetMinorVersion());
	buffer.StringAppend(line.GetBuffer() );
	buffer.StringAppend("\r\n");

	buffer.StringAppend("Memory:    \t");
	MStdSPrintf(line.GetBuffer(),line.GetSize()-2,"%d MB",machinfo.GetPhysicalMemoryMB() );
	buffer.StringAppend(line.GetBuffer() );
	buffer.StringAppend("\r\n");

	buffer.StringAppend("Windows Dir:\t");
	buffer.StringAppend(machinfo.GetWindowsDir() );
	buffer.StringAppend("\r\n");

	buffer.StringAppend("System Dir: \t");
	buffer.StringAppend(machinfo.GetSystemDir() );
	buffer.StringAppend("\r\n");



	
	// Display Information
	MStdSPrintf(line.GetBuffer(),line.GetSize()-2,"%s v%s",GApplicationName,GApplicationVersion);
	MStdWindowOutput(line.GetBuffer(),buffer.GetBuffer());
	
	return 0;
	}


