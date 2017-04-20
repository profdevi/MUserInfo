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

//v1.2 copyright Comine.com 20160214U2007
#ifndef MWinShellInfo_h
#define MWinShellInfo_h

/////////////////////////////////////////////
#include "MStdLib.h"
#include "MBuffer.h"

//******************************************************
//**  MWinShellInfo class
//******************************************************
class MWinShellInfo
	{
	////////////////////////////////////////////////
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MWinShellInfo(bool create=false);
	~MWinShellInfo(void);
	bool Create(void);
	bool Destroy(void);
	bool GetDir(int csidl,MBuffer &outbuf);				// Get Info based on CSIDL 

	bool GetWindowsDir(MBuffer &outdir);				// Get Windows Directory
	bool GetWindowsSystemDir(MBuffer &outdir);			// Get System Directory
	bool GetUserAppDataLocalDir(MBuffer &outdir);		// Local App Data
	bool GetUserAppDataLocalLowDir(MBuffer &outdir);	// Local App Data
	bool GetUserAppDataRoamingDir(MBuffer &outdir);		// Get App Data
	bool GetUserDesktopDir(MBuffer &outdir);			// Get User Desktop Directory
	bool GetUserRecentDir(MBuffer &outdir);				// Get User Recent Folder	
	bool GetUserStartUpDir(MBuffer &outdir);			// Get the user startup dir
	bool GetUserInternetCacheDir(MBuffer &outdir);		// Get Internet Cache Directory
	bool GetUserInternetCookiesDir(MBuffer &outdir);	// Get Internet Cookies Folder
	bool GetUserInternetHistoryDir(MBuffer &outdir);	// Get Internet History Folder
	bool GetAllDesktopDir(MBuffer &outdir);				// Get Everyone's Desktop Directory	
	bool GetAllStartUpDir(MBuffer &outdir);				// Get the user startup dir

	bool Print(void);									// Print out the dirs for info
	};

#endif // MWinShellInfo_h
