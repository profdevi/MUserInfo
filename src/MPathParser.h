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

//v1.10 copyright Comine.com 20160718M0708
#ifndef MPathParser_h
#define MPathParser_h

/////////////////////////////////////////////////////
#include "MBuffer.h"

//******************************************************
//**  MPathParser class
//******************************************************
class MPathParser
	{
	////////////////////////////////////////////////
	MBuffer mBuffer;			// Memory buffer to hold all data
	char *mDrive;				// Holds the Drive Letter
	char *mDir;					// Holds the Directory Name
	char *mFileName;			// Holds the FileName
	char *mFileExt;				// Holds the file ext
	char *mPath;				// Holds the Path
	char *mFullFileName;		// Holds Full File name
	
	////////////////////////////////////////////////
	void ClearObject(void);
	void MakePathNames(void);	// Make a pathname

	////////////////////////////////////////////////
	public:
	MPathParser(bool init=false);
	~MPathParser(void);
	bool Create(void);
	bool Destroy(void);
	bool SetDrive(const char *drive);					// Change Drive
	bool SetDir(const char *dir);						// Set the Directory
	bool SetDriveDir(const char *dir);					// Set the Dir Path with drive
	bool SetFileName(const char *filename);				// Set the Filename
	bool SetFileExt(const char *extension);				// Set the File Extension
	bool SetPath(const char *path);						// Set the File path
	bool SetFullFileName(const char *filename);			// Set Filename as "One.txt";
	const char *GetDrive(void);							// Get Drive
	const char *GetDir(void);							// Get File Dir
	const char *GetFileName(void);						// Get File Name
	const char *GetFileExt(void);						// Get File Extension
	const char *GetPath(void);							// Get File Path
	const char *GetFullFileName(void);					// Get Full File name(ie "one.txt")
	bool Clear(void);									// Clear all the elements
	bool SetFileNameInExeHome(const char *filename);	// "help.hlp"
	};

#endif // MPathParser_h

