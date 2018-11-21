// Settings.cpp: implementation of the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "Settings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "atreg.h"

#define IDS_ROOTKEYPATH _T("Software\\SoftCentral\\SC-QuickStart")
#ifndef IDS_APPTITLE
	#define IDS_APPTITLE _T("SC-QuickStart")
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettings::CSettings()
{

}

CSettings::~CSettings()
{

}

void CSettings::Set(LPCTSTR szValueName, LPCTSTR szValue)
{
	HKEY hKey = GetRootKey(KEY_WRITE);
	if (hKey)
	{
		RegSetValueEx(hKey, szValueName, 0, REG_SZ, (LPBYTE)szValue, strlen(szValue)+1);
		RegCloseKey(hKey);
	}
}

void CSettings::Set(LPCTSTR szValueName, DWORD dwValue)
{
	HKEY hKey = GetRootKey(KEY_WRITE);
	if (hKey)
	{
		RegSetValueEx(hKey, szValueName, 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(dwValue));
		RegCloseKey(hKey);
	}
}
void CSettings::Set(LPCTSTR szValueName, BYTE* pData, DWORD dwcbData )
{
	HKEY hKey = GetRootKey(KEY_WRITE);
	if (hKey)
	{
		RegSetValueEx(hKey, szValueName, 0, REG_BINARY, pData, dwcbData);
		RegCloseKey(hKey);
	}
}


// returns -1 on failure
CString CSettings::GetS(LPCTSTR szValueName)
{
	HKEY hKey = GetRootKey(KEY_READ);
	char szRet[MAX_PATH]="-1";
	if (hKey)
	{
		DWORD dwType, dwSize=MAX_PATH;
		RegQueryValueEx(hKey, szValueName, 0, &dwType, (LPBYTE)szRet, &dwSize);
		RegCloseKey(hKey);
	}
	return szRet;
}

// returns -1 on failure
DWORD CSettings::GetDW(LPCTSTR szValueName, DWORD dwDefaultSetting)
{
	HKEY hKey = GetRootKey(KEY_READ);
	DWORD dwRet=-1;
	if (hKey)
	{
		DWORD dwType, dwSize=sizeof(DWORD);
		if (ERROR_SUCCESS != RegQueryValueEx(hKey, szValueName
			, 0, &dwType, (LPBYTE)&dwRet, &dwSize))
		{
			if (dwDefaultSetting != -1)
			{
				Set(szValueName, dwDefaultSetting);
				dwRet=dwDefaultSetting;
			}
			else
				dwRet=-1;
		}
		RegCloseKey(hKey);
	}
	return dwRet;
}

// returns -1 on failure
int CSettings::GetB(LPCTSTR szValueName, LPBYTE pData, DWORD* pdwcb)
{
	HKEY hKey = GetRootKey(KEY_READ);
	int iRet=-1;
	if (hKey)
	{
		DWORD dwType;
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, szValueName
			, 0, &dwType, pData, pdwcb))
			iRet=1;
		else
			RegCloseKey(hKey);
		
	}
	return iRet;
}


HKEY CSettings::GetRootKey(REGSAM Sam)
{
	HKEY hKey=0;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, IDS_ROOTKEYPATH
		, 0, Sam, &hKey) )
	{
		CATReg reg;
		reg.RegCreateFullKeyPath(HKEY_LOCAL_MACHINE, IDS_ROOTKEYPATH, Sam, &hKey);
	}
	return hKey;
}

void CSettings::EnableAutoStart(BOOL bEnable)
{
	HKEY hKey;
	if (ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE
		, "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
		, 0
		, KEY_WRITE
		, &hKey))
	{
		if (!bEnable)
			RegDeleteValue(hKey, IDS_APPTITLE);
		else
		{
			char szPath[MAX_PATH];
			if (GetModuleFileName(NULL, szPath, MAX_PATH))
				RegSetValueEx(hKey, IDS_APPTITLE, 0
					, REG_SZ, (LPBYTE)szPath, strlen(szPath));
		}

		RegCloseKey(hKey);
	}
}