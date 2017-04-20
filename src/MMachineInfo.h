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

//v1.10 copyright Comine.com 20170412W1622
#ifndef MMachineInfo_h
#define MMachineInfo_h

//////////////////////////////////////////////
#include <windows.h>
#include "MStdLib.h"

//////////////////////////////////////////////
class MMachineInfo
	{
	OSVERSIONINFOA *mVersionInfo;
	char *mMachineName;
	char *mWindowsDirectory;
	char *mSystemDirectory;
	MEMORYSTATUSEX *mMemInfo;

	//////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////
	public:
	MMachineInfo(bool create=false);
	~MMachineInfo(void);
	bool Create(void);
	bool Destroy(void);
	int GetMajorVersion(void);
	int GetMinorVersion(void);
	int GetBuildNumber(void);
	const char *GetCSDVersion(void);
	const char *GetVersionInfo(void);
	const char *GetMachineName(void);
	const char *GetWindowsDir(void);
	const char *GetSystemDir(void);
	bool SetMachineName(const char *name);
	const char *GetOSName(void);
	int GetMemoryInUsePercent(void);
	int GetPhysicalMemoryMB(void);
	int GetPhysicalMemoryAvailibleMB(void);
	int GetVirtualMemoryMB(void);
	int GetVirtualMemoryAvailibleMB(void);
	const char *GetCPUInfo(void);					// String Identifying CPU
	};


#endif // MMachineInfo_h

