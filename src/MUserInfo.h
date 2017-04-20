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
#ifndef MUserInfo_h
#define MUserInfo_h

///////////////////////////////////////////////////
#include "MString.h"

//******************************************************
//**  MUserInfo class
//******************************************************
class MUserInfo
	{
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MUserInfo(void);
	MUserInfo(bool create);
	~MUserInfo(void);
	bool Create(void);
	bool Destroy(void);
	bool GetUserNameString(MString &name);
	bool IsAdministrator(void);
	bool GetHomeDir(MString &dir);
	bool GetDesktopDir(MString &dir);
	bool GetAllUsersDir(MString &dir);
	bool GetAllUsersDesktopDir(MString &dir);
	bool GetLocalAppDataDir(MString &dir);
	};

#endif // MUserInfo_h

