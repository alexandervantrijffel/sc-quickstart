// SHRetr.cpp: implementation of the CSHRetr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "shretr.h"

#include "ATReg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define IDS_APPPATHS "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSHRetr::CSHRetr()
{

}

CSHRetr::~CSHRetr()
{

}

HICON CSHRetr::GetIcon(LPCTSTR szPath)
{
	// check for directory
	DWORD dwAttr = GetFileAttributes(szPath);
	if ( dwAttr != -1 && dwAttr & FILE_ATTRIBUTE_DIRECTORY)

		return GetFolderIcon();

	LPCTSTR szExt = strrchr(szPath, '.');

	// check for executable 
	if (!szExt || 0 == stricmp(szExt+1, "exe") || 0 == stricmp(szExt+1, "dll"))
		return GetIcon(szPath, 0);
	else
	{
		char szPath[MAX_PATH] = "";
		DWORD dwcb=MAX_PATH;
		CATReg reg;
						
		// get the descriptive name of the filetype
		if (ERROR_SUCCESS == reg.RegGetVal(HKEY_CLASSES_ROOT, szExt, 0, szPath, &dwcb))
		{
			dwcb=MAX_PATH;
			sprintf(szPath, "%s\\DefaultIcon", szPath);
			
			// get the location of the icon with the index
			if (ERROR_SUCCESS == reg.RegGetVal(HKEY_CLASSES_ROOT, szPath, 0, szPath, &dwcb))
				return GetIconFromRegString(szPath);
		}
	}
			
	return 0;
}

HICON CSHRetr::GetFolderIcon()
{
	CATReg reg;
	DWORD dwcb=MAX_PATH;
	char szPath[MAX_PATH];
	
	if (ERROR_SUCCESS == reg.RegGetVal(HKEY_CLASSES_ROOT
		, "Folder\\DefaultIcon", 0, szPath, &dwcb))
			return GetIconFromRegString(szPath);

	return 0;
}	

HICON CSHRetr::GetIconFromRegString(LPTSTR szFormattedString)
{
	int iIndex=0;

	// the index of the icon is located after the comma
	LPTSTR szPos = strrchr(szFormattedString, ',');
	if (szPos) 
	{
		iIndex = atoi(szPos+1);
		*szPos = 0;
	}
	return GetIcon(szFormattedString, iIndex);
}

HICON CSHRetr::GetIcon(LPCTSTR szFile, UINT nIndex)
{
	HICON hIc = ExtractIcon(AfxGetInstanceHandle(), szFile, nIndex);
	if (hIc <= (HICON) 1)
		hIc = 0;

	return hIc;
}

HICON CSHRetr::GetCDIcon()
{
	SHFILEINFO shFinfo;
	HIMAGELIST hImgList = NULL;

	CString szDrives = GetAllCDDrives();
	if (szDrives.GetLength())
	{
		szDrives.Format("%c:\\", szDrives.GetAt(0) );

		hImgList = (HIMAGELIST)SHGetFileInfo( szDrives,
							  0,
							  &shFinfo,
							  sizeof( shFinfo ),
							  SHGFI_ICON);
		if ( !hImgList )
			return FALSE; 

		HICON hIconRet = shFinfo.hIcon;

		ImageList_Destroy(hImgList);
		return hIconRet;
	}

	return 0;
}

CString CSHRetr::GetAllCDDrives()
{
	CString szDrives;
	TCHAR szDrive[4];
	strcpy(szDrive, "?:\\");
	int nPos = 0;

	DWORD dwDriveList = ::GetLogicalDrives ();
	while (dwDriveList) 
	{
		if (dwDriveList & 1) 
		{
			szDrive[0] = 0x41 + nPos;
			if(::GetDriveType(szDrive) == DRIVE_CDROM)
				szDrives += szDrive[0];
		}
		dwDriveList >>= 1;
		nPos++;
	}

	return szDrives;
}

HICON CSHRetr::GetURLIcon()
{
	HICON hIcon = GetIcon(".htm");
	if (!hIcon)
		hIcon = GetIcon(".html");
	return hIcon;
}

HICON CSHRetr::GetIcon( LPITEMIDLIST lpi, BOOL bSmallIcon )
{
	SHFILEINFO sfi;
	UINT uFlags = SHGFI_PIDL | SHGFI_ICON | ((bSmallIcon) ? SHGFI_SMALLICON : 0);
    SHGetFileInfo( (LPCSTR)lpi, 0, &sfi, sizeof( sfi ), uFlags );
  	
	return sfi.hIcon;
}

HICON CSHRetr::GetSpecialFolderIcon(int nFolder)
{
	LPMALLOC		lpMalloc=0;
	HICON			hIcon = 0;
	LPITEMIDLIST    lpi=NULL;

	// Allocate a shell memory object. 
	if (FAILED(::SHGetMalloc(&lpMalloc)))
		return 0;

	if (NOERROR == SHGetSpecialFolderLocation(NULL, nFolder, &lpi))
	{
		hIcon = GetIcon(lpi, FALSE);

		lpMalloc->Free(lpi);
		lpMalloc->Release();
	}

	return hIcon;
}

// int nFolder is een id uit SHGetSpecialFolderLocation
//
BOOL CSHRetr::InvokeCmd(int nFolder, LPCTSTR szVerb)
{
	LPSHELLFOLDER lpsf=0;
	LPSHELLFOLDER lpsf2=0;
	LPITEMIDLIST lpi=0;
	LPMALLOC lpMalloc=0;
	BOOL bSuccess=FALSE;

	// Allocate a shell memory object. 
	if (FAILED(::SHGetMalloc(&lpMalloc)))
		return FALSE;
	
	try
	{
		// get desktop shell folder
		if (FAILED(::SHGetDesktopFolder(&lpsf)))
			throw 0;

		// get my computer shell folder
		if (NOERROR != SHGetSpecialFolderLocation(NULL, nFolder, &lpi))
			throw 0;

		if (FAILED(lpsf->BindToObject(lpi, 0, IID_IShellFolder
			, (LPVOID*)&lpsf2)))
			throw 0;

		LPCONTEXTMENU lpcm;
		HRESULT       hr;
    	CMINVOKECOMMANDINFO cmi;
		DWORD               dwAttribs=0;
	
		hr=lpsf->GetUIObjectOf(NULL,
		    1,  //Number of objects to get attributes of
			(const struct _ITEMIDLIST **)&lpi,
			IID_IContextMenu,
			0,
			(LPVOID *)&lpcm);
		
		if (FAILED(hr))
			throw 0;
			
		HMENU hMenu = CreatePopupMenu();

		if (!hMenu)
			throw 0;

		hr=lpcm->QueryContextMenu(hMenu, 0, 1, 0x7fff, CMF_EXPLORE);
        if (SUCCEEDED(hr))
        {
/*			char sz[64]="";
			for (int i=0 ; i<2 ; i++)
			{
				if (::GetMenuString(hMenu, i, sz, 64, MF_BYPOSITION))
				{
					TRACE2 ("txt=%s i=%d\n", sz, i);
					if (0 == stricmp(szVerb, sz))
						break;

				}
			}
*/			
			// get menu item ID of Cmd open or explore
			UINT nID = GetMenuItemID(hMenu, (0 == strcmp(szVerb, "Explore"))?0:1);
			
			cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
	        cmi.fMask  = CMIC_MASK_FLAG_NO_UI;
			cmi.hwnd   = 0;
			cmi.lpVerb = MAKEINTRESOURCE(nID-1);
			cmi.lpParameters = NULL;
      		cmi.lpDirectory  = NULL;
			cmi.nShow        = SW_SHOWNORMAL;
			cmi.dwHotKey     = 0;
			cmi.hIcon        = NULL;
			hr=lpcm->InvokeCommand(&cmi);

	/*		char sz[64]="";
			for (int i=0; i<200; i++)
			{
				cmi.lpVerb = MAKEINTRESOURCE(i);
				if (SUCCEEDED(lpcm->InvokeCommand(&cmi)))
				{
					char szSum[4];
					itoa(i, szSum, 10);
					// sysproperties 19
					// manage 45
					// explore 46
					// open 47
					
					if (NOERROR == lpcm->GetCommandString(i, GCS_VERB , 0, sz, 64))
					{
						strcat(sz, szSum);
						AfxMessageBox(sz);
					}
					else
						AfxMessageBox(szSum);
				}
			}
	*/			
			bSuccess = SUCCEEDED(hr);

			lpcm->Release();
	    } 

	}
	catch (int i)
	{
		i=0;
	}
	if (lpi)
		lpMalloc->Free(lpi);
		
	lpMalloc->Release();

	if (lpsf)
		lpsf->Release();
	if (lpsf2)
		lpsf2->Release();

    return bSuccess;
}

// bonus function

CString CSHRetr::GetAppPath(LPCTSTR szFileName)
{
	char szPath[MAX_PATH];
	sprintf(szPath, "%s\\%s", IDS_APPPATHS, szFileName);

	CATReg reg;
	DWORD dwcb=MAX_PATH;
	
	if (ERROR_SUCCESS != reg.RegGetVal(HKEY_LOCAL_MACHINE, szPath, 0, szPath, &dwcb))
		szPath[0] = 0;

	return szPath;
}

HCURSOR CSHRetr::GetHandCursor()
{
	HCURSOR hHandCursor = 0;

		// Get the windows directory
        CString strWndDir;
        GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
        strWndDir.ReleaseBuffer();

        strWndDir += _T("\\winhlp32.exe");
        // This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
        HMODULE hModule = LoadLibrary(strWndDir);
        if (hModule) {
            hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
            
        }
        FreeLibrary(hModule);
	return hHandCursor;
}
