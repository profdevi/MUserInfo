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

//v1.8 copyright Comine.com 20170412W1625
#include <windows.h>
#include "MStdLib.h"
#include "MBuffer.h"
#include "MString.h"
#include "MPathParser.h"
#include "MFileOps.h"
#include "MUserInfo.h"


///////////////////////////////////////////////
// Link Library
#pragma comment(lib,"advapi32.lib")

//******************************************************
//**  Module Info
//******************************************************
static const int GBufferSize=2048;


//******************************************************
//**  MUserInfo class
//******************************************************
void MUserInfo::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MUserInfo::MUserInfo(void)
	{  ClearObject();  }


/////////////////////////////////////////////////
MUserInfo::MUserInfo(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}

////////////////////////////////////////////////
MUserInfo::~MUserInfo(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MUserInfo::Create(void)
	{
	Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MUserInfo::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MUserInfo::GetUserNameString(MString &name)
	{
	MBuffer buffer;
	if(buffer.Create(GBufferSize)==false)
		{
		return false;
		}

	// Get Win32 User Name
	 DWORD size=buffer.GetSize()-1;
	if(::GetUserNameA(buffer.GetBuffer(),&size)==FALSE)
		{
		return false;
		}

	if(name.Create(buffer.GetBuffer())==false)
		{
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////
bool MUserInfo::IsAdministrator(void)
	{
	///////////////////////////////////////
	MString userinfo;
	if(GetUserNameString(userinfo)==false) {  return false;  }

	if(MString::ICompare(userinfo.Get(),"Administrator")==0) { return true; }

	return false;
	}


/////////////////////////////////////////////////
bool MUserInfo::GetHomeDir(MString &dir)
	{
	////////////////////////////////////////////
	MBuffer buffer;
	if(buffer.Create(GBufferSize)==false)
		{
		return false;
		}

	////////////////////////////////////////////
	DWORD retval=GetEnvironmentVariableA("USERPROFILE",buffer.GetBuffer()
			,buffer.GetSize()-1);
	if(retval==0)
		{
		return false;
		}

	if(retval>=(DWORD)(buffer.GetSize()-1) )
		{
		return false;
		}

	// Check if path is good
	if(buffer.GetStringLength()<=1)
		{
		return false;
		}

	if(dir.Create(buffer.GetBuffer())==false)
		{
		return false;
		}

	// Check if directory exists
	MFileOps fileops;
	if(fileops.Create()==false)
		{
		return false;
		}

	if(fileops.IsDirectory(dir.Get())==false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////
bool MUserInfo::GetDesktopDir(MString &dir)
	{
	MString homedir;
	if(GetHomeDir(homedir)==false){  return false;  }
	
	MPathParser path;
	if(path.Create()==false)
		{
		return false;
		}

	if(path.SetDriveDir(homedir.Get())==false ||
			path.SetFileName("Desktop")==false )
		{
		return false;
		}

	if(dir.Create(path.GetPath())==false)
		{
		return false;
		}

	// Check if directory exists
	MFileOps fileops;
	if(fileops.Create()==false)
		{
		return false;
		}

	if(fileops.IsDirectory(dir.Get())==false)
		{
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////
bool MUserInfo::GetAllUsersDir(MString &dir)
	{
	////////////////////////////////////////////
	MBuffer buffer;
	if(buffer.Create(GBufferSize)==false)
		{
		return false;
		}

	////////////////////////////////////////////
	DWORD retval=GetEnvironmentVariableA("ALLUSERSPROFILE",buffer.GetBuffer()
			,buffer.GetSize()-1);
	if(retval==0)
		{
		return false;
		}

	if(retval>=(DWORD)(buffer.GetSize()-1) )
		{
		return false;
		}

	// Check if path is good
	if(buffer.GetStringLength()<=1)
		{
		return false;
		}

	if(dir.Create(buffer.GetBuffer())==false)
		{
		return false;
		}

	// Check if directory exists
	MFileOps fileops;
	if(fileops.Create()==false)
		{
		return false;
		}

	if(fileops.IsDirectory(dir.Get())==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////////////
bool MUserInfo::GetAllUsersDesktopDir(MString &dir)
	{
	MString homedir;
	if(GetAllUsersDir(homedir)==false){  return false;  }
	
	MPathParser path;
	if(path.Create()==false)
		{
		return false;
		}

	if(path.SetDriveDir(homedir.Get())==false ||
			path.SetFileName("Desktop")==false )
		{
		return false;
		}

	if(dir.Create(path.GetPath())==false)
		{
		return false;
		}

	// Check if directory exists
	MFileOps fileops;
	if(fileops.Create()==false)
		{
		return false;
		}

	if(fileops.IsDirectory(dir.Get())==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MUserInfo::GetLocalAppDataDir(MString &dir)
	{
	////////////////////////////////////////////
	MBuffer buffer;
	if(buffer.Create(GBufferSize)==false)
		{
		return false;
		}

	////////////////////////////////////////////
	DWORD retval=GetEnvironmentVariableA("LOCALAPPDATA",buffer.GetBuffer()
			,buffer.GetSize()-1);
	if(retval>1)
		{
		// Check if directory exists
		MFileOps fileops;
		if(fileops.Create()==false)
			{
			return false;
			}

		if(fileops.IsDirectory(buffer.GetBuffer())==false)
			{
			return false;
			}

		if(dir.Create(buffer.GetBuffer())==false)
			{
			return false;
			}

		return true;
		}

	//=No environment variable LOCALAPPDIR
	MString homedir;
	if(GetHomeDir(homedir)==false)
		{
		return false;
		}
	
	// Build up the path expected
	MBuffer dirpath;
	if(dirpath.Create(GBufferSize)==false)
		{
		return false;
		}

	MStdSPrintf(dirpath.GetBuffer(),dirpath.GetSize(),
			"%s\\Local Settings\\Application Data",homedir.Get() );
	
	// Check if directory exists
	MFileOps fileops;
	if(fileops.Create()==false)
		{
		return false;
		}

	if(fileops.IsDirectory(dirpath.GetBuffer() )==false)
		{
		return false;
		}

	if(dir.Create(dirpath.GetBuffer())==false)
		{
		return false;
		}
	
	return true;
	}

