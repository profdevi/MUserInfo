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
#include <windows.h>
#include "MStdLib.h"
#include "MMachineInfo.h"


///////////////////////////////////////
#ifdef MSTDLIB_OS_WINDOWS
#pragma comment(lib,"kernel32.lib")
#endif // MSTDLIB_IS_WINDOWS

//*****************************************************************
//** Module Info
//*****************************************************************
/*
	This CPUInfo code lifted from 
*/
static char GCPUInfoBuffer[100];
const char *GGetCPUInfo(void)
	{
	MStdMemZero(GCPUInfoBuffer,50);
	_asm {
		mov eax, 80000002h
		cpuid

		mov BYTE PTR GCPUInfoBuffer[0], al
		mov BYTE PTR GCPUInfoBuffer[1], ah
		ror eax, 16
		mov BYTE PTR GCPUInfoBuffer[2], al
		mov BYTE PTR GCPUInfoBuffer[3], ah

		mov BYTE PTR GCPUInfoBuffer[4], bl
		mov BYTE PTR GCPUInfoBuffer[5], bh
		ror ebx, 16
		mov BYTE PTR GCPUInfoBuffer[6], bl
		mov BYTE PTR GCPUInfoBuffer[7], bh

		mov BYTE PTR GCPUInfoBuffer[8], cl
		mov BYTE PTR GCPUInfoBuffer[9], ch
		ror ecx, 16
		mov BYTE PTR GCPUInfoBuffer[10], cl
		mov BYTE PTR GCPUInfoBuffer[11], ch

		mov BYTE PTR GCPUInfoBuffer[12], dl
		mov BYTE PTR GCPUInfoBuffer[13], dh
		ror edx, 16
		mov BYTE PTR GCPUInfoBuffer[14], dl
		mov BYTE PTR GCPUInfoBuffer[15], dh

		mov eax, 80000003h
		cpuid

		mov BYTE PTR GCPUInfoBuffer[16], al
		mov BYTE PTR GCPUInfoBuffer[17], ah
		ror eax, 16
		mov BYTE PTR GCPUInfoBuffer[18], al
		mov BYTE PTR GCPUInfoBuffer[19], ah
	
		mov BYTE PTR GCPUInfoBuffer[20], bl
		mov BYTE PTR GCPUInfoBuffer[21], bh
		ror ebx, 16
		mov BYTE PTR GCPUInfoBuffer[22], bl
		mov BYTE PTR GCPUInfoBuffer[23], bh

		mov BYTE PTR GCPUInfoBuffer[24], cl
		mov BYTE PTR GCPUInfoBuffer[25], ch
		ror ecx, 16
		mov BYTE PTR GCPUInfoBuffer[26], cl
		mov BYTE PTR GCPUInfoBuffer[27], ch

		mov BYTE PTR GCPUInfoBuffer[28], dl
		mov BYTE PTR GCPUInfoBuffer[29], dh
		ror edx, 16
		mov BYTE PTR GCPUInfoBuffer[30], dl
		mov BYTE PTR GCPUInfoBuffer[31], dh

		mov eax, 80000004h
		cpuid

		mov BYTE PTR GCPUInfoBuffer[32], al
		mov BYTE PTR GCPUInfoBuffer[33], ah
		ror eax, 16
		mov BYTE PTR GCPUInfoBuffer[34], al
		mov BYTE PTR GCPUInfoBuffer[35], ah

		mov BYTE PTR GCPUInfoBuffer[36], bl
		mov BYTE PTR GCPUInfoBuffer[37], bh
		ror ebx, 16
		mov BYTE PTR GCPUInfoBuffer[38], bl
		mov BYTE PTR GCPUInfoBuffer[39], bh

		mov BYTE PTR GCPUInfoBuffer[40], cl
		mov BYTE PTR GCPUInfoBuffer[41], ch
		ror ecx, 16
		mov BYTE PTR GCPUInfoBuffer[42], cl
		mov BYTE PTR GCPUInfoBuffer[43], ch

		mov BYTE PTR GCPUInfoBuffer[44], dl
		mov BYTE PTR GCPUInfoBuffer[45], dh
		ror edx, 16
		mov BYTE PTR GCPUInfoBuffer[46], dl
		mov BYTE PTR GCPUInfoBuffer[47], dh
		}

	GCPUInfoBuffer[48] = '\0';

	return GCPUInfoBuffer;
	}


//*****************************************************************
//** MMachine Info
//*****************************************************************
void MMachineInfo::ClearObject(void)
	{
	mVersionInfo=NULL;
	mMachineName=NULL;
	mWindowsDirectory=NULL;
	mSystemDirectory=NULL;
	mMemInfo=NULL;
	}


////////////////////////////////////////////////////////////
MMachineInfo::MMachineInfo(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////////////////
MMachineInfo::~MMachineInfo(void)
	{  Destroy();  }


////////////////////////////////////////////////////////////
bool MMachineInfo::Create(void)
	{
	Destroy();

	// Allocate space for data
	mVersionInfo=new(std::nothrow) OSVERSIONINFOA;
	mMachineName=new(std::nothrow) char[MAX_COMPUTERNAME_LENGTH+1];
	mWindowsDirectory=new(std::nothrow) char[MAX_PATH+1];
	mSystemDirectory=new(std::nothrow) char[MAX_PATH+1];
	mMemInfo=new(std::nothrow) MEMORYSTATUSEX;

	if(	mVersionInfo==NULL || mMachineName==NULL
			|| mWindowsDirectory==NULL || mSystemDirectory==NULL 
			|| mMemInfo==NULL)
		{
		Destroy();
		return false;
		}


	// Init Infor
	MStdMemSet(mVersionInfo,0,sizeof(*mVersionInfo) );
	mVersionInfo->dwOSVersionInfoSize=sizeof(*mVersionInfo);

	if(GetVersionExA((LPOSVERSIONINFOA)mVersionInfo)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get Machine Name
	DWORD namesize=MAX_COMPUTERNAME_LENGTH+1;
	if(GetComputerNameA(mMachineName,&namesize)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get Windows Directory
	if(GetWindowsDirectoryA(mWindowsDirectory,MAX_PATH+1)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get System Directory
	if(GetSystemDirectoryA(mSystemDirectory,MAX_PATH+1)==FALSE)
		{
		Destroy();
		return false;
		}

	// Get MMemoryInfo
	MStdMemZero(mMemInfo,sizeof(*mMemInfo) );
	mMemInfo->dwLength = sizeof(*mMemInfo);

	if(GlobalMemoryStatusEx(mMemInfo)==FALSE)
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////////////
bool MMachineInfo::Destroy(void)
	{
	if(mVersionInfo!=NULL)
		{
		delete mVersionInfo;
		mVersionInfo=NULL;
		}

	if(mMachineName!=NULL)
		{
		delete[] mMachineName;
		mMachineName=NULL;
		}

	if(mSystemDirectory!=NULL)
		{
		delete[] mSystemDirectory;
		mSystemDirectory=NULL;
		}

	if(mWindowsDirectory!=NULL)
		{
		delete[] mWindowsDirectory;
		mWindowsDirectory=NULL;
		}

	if(mMemInfo!=NULL)
		{
		delete mMemInfo;
		mMemInfo=NULL;
		}

	ClearObject();
	return true;
	}


////////////////////////////////////////////////////////////
int MMachineInfo::GetMajorVersion(void)
	{
	return (int)mVersionInfo->dwMajorVersion;
	}


////////////////////////////////////////////////////////////
int MMachineInfo::GetMinorVersion(void)
	{
	return (int)mVersionInfo->dwMinorVersion;
	}


////////////////////////////////////////////////////////////
int MMachineInfo::GetBuildNumber(void)
	{
	return (int)mVersionInfo->dwBuildNumber;
	}


/////////////////////////////////////////////////////////////
const char *MMachineInfo::GetCSDVersion(void)
	{
	return mVersionInfo->szCSDVersion;
	}


////////////////////////////////////////////////////////////
const char *MMachineInfo::GetVersionInfo(void)
	{
	return mVersionInfo->szCSDVersion;
	}


///////////////////////////////////////////////////////////
const char *MMachineInfo::GetMachineName(void)
	{
	return mMachineName;
	}


///////////////////////////////////////////////////////////
const char *MMachineInfo::GetWindowsDir(void)
	{
	return mWindowsDirectory;
	}


///////////////////////////////////////////////////////////
const char *MMachineInfo::GetSystemDir(void)
	{
	return mSystemDirectory;
	}


//////////////////////////////////////////////////////////
bool MMachineInfo::SetMachineName(const char *name)
	{
	if(name==NULL || *name==0)
		{
		// COmputer Name is bad
		return false;
		}
	if(::SetComputerNameA(name)==FALSE)
		{
		// Unable to set computer name
		return false;
		}

	return true;	
	}


////////////////////////////////////////////////////////
const char *MMachineInfo::GetOSName(void)
	{
	const int majorid=GetMajorVersion();
	const int minorid=GetMinorVersion();
	const char *csdversion=GetCSDVersion();
	
	// Ref: http://www.codeguru.com/cpp/misc/misc/system/article.php/c8973
	if(majorid==3)
		{
		return "Windows NT 3.5";
		}
	else if(majorid==4)
		{
		if(minorid==0)
			{
			if(*csdversion=='C' || *csdversion=='B')
				{
				return "Windows 95 ISR2";
				}

			return "Windows 95";
			}
		else if(minorid==10)
			{
			if(*csdversion=='A')
				{
				return "Windows 98 SE";
				}

			return "Windows 98";
			}
		else if(minorid==90)
			{
			return "Windows ME";
			}

		return "Windows NT 4";
		}
	else if(majorid==5)
		{
		if(minorid==0)
			{
			return "Windows 2000";
			}
		else if(minorid==1)
			{
			return "Windows XP";
			}
		else if(minorid==2)
			{
			return "Windows XP Pro 64";
			}

		return "Windows XP";
		}
	else if(majorid==6)
		{
		if(minorid==0)
			{
			return "Windows Vista";
			}
		else if(minorid==1)
			{
			return "Windows 7";
			}
		else if(minorid==2)
			{
			return "Windows 8";
			}
		}

	return "Unknown Windows";
	}


/////////////////////////////////////////////
int MMachineInfo::GetMemoryInUsePercent(void)
	{
	return (int)mMemInfo->dwMemoryLoad;
	}


//////////////////////////////////////////////
int MMachineInfo::GetPhysicalMemoryMB(void)
	{
	return (int)(mMemInfo->ullTotalPhys/(1024*1024) );
	}


/////////////////////////////////////////////
int MMachineInfo::GetPhysicalMemoryAvailibleMB(void)
	{
	return (int)(mMemInfo->ullAvailPhys/(1024*1024) );
	}


//////////////////////////////////////////////
int MMachineInfo::GetVirtualMemoryMB(void)
	{
	return (int)(mMemInfo->ullTotalVirtual/(1024*1024) );
	}


///////////////////////////////////////////////
int MMachineInfo::GetVirtualMemoryAvailibleMB(void)
	{
	return (int)(mMemInfo->ullAvailVirtual/(1024*1024) );
	}


//////////////////////////////////////////////
const char *MMachineInfo::GetCPUInfo(void)
	{
	return GGetCPUInfo();
	}	


