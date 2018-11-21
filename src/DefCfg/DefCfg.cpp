// DefCfg.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "DefCfg.h"

DWORD dwCount=1;
// for addqso structure
#include "../QuickStart/qsoinfo.h"
#define IDS_APPPATHS "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

void DEFCFG_API PASCAL GetFirstCfg(LPVOID lpQSOInfo)
{
	PADDQSO_INFOC pInfo = (PADDQSO_INFOC)lpQSOInfo;

	pInfo->dwHotKey = (MOD_CONTROL<<9)|VK_F2 ;
	strcpy(pInfo->szName, "Soft-Central");
	strcpy(pInfo->szPath, "http://www.soft-central.net");
	strcpy(pInfo->szOpt, "open");
}

BOOL DEFCFG_API PASCAL GetNextCfg(LPVOID lpQSOInfo)
{

	PADDQSO_INFOC pInfo = (PADDQSO_INFOC)lpQSOInfo;
	
	pInfo->dwHotKey++;
	
	switch (dwCount)
	{
		case 1:
			pInfo->szOpt[0]=0;
			strcpy(pInfo->szName, "Word");
			if (GetAppPath("winword.exe", pInfo->szPath))
				break;

			strcpy(pInfo->szName, "Wordpad");
			if (GetAppPath("wordpad.exe", pInfo->szPath))
				break;

			dwCount++;

		case 2:
			strcpy(pInfo->szName, "Excel");
			if (GetAppPath("excel.exe", pInfo->szPath))
				break;
			dwCount++;

		case 3:	
			strcpy(pInfo->szName, "Outlook");
			if (GetAppPath("outlook.exe", pInfo->szPath))
				break;
			dwCount++;

		case 4:	
			strcpy(pInfo->szName, "Paintbrush");
			if (GetAppPath("pbrush.exe", pInfo->szPath))
				break;
			dwCount++;

		case 5:	
			strcpy(pInfo->szName, "Outlook Express");
			if (GetAppPath("msimn.exe", pInfo->szPath))
				break;
			dwCount++;
		case 6:
			strcpy(pInfo->szName, "Control Panel");
			strcpy(pInfo->szPath, "€5");
			break;
			
		case 7:
			// COM+ supported?
			OSVERSIONINFO vi;
			vi.dwOSVersionInfoSize=sizeof(vi);
			if (GetVersionEx(&vi) && vi.dwMajorVersion > 4)
			{
				strcpy(pInfo->szName, "Empty Recycle Bin");
				strcpy(pInfo->szPath, "€10");
				break;
			}

			dwCount++;

		case 8 :
			strcpy(pInfo->szName, "Shutdown");
			strcpy(pInfo->szPath, "€2");
			strcpy(pInfo->szOpt, "0");
			break;

		case 9:
			strcpy(pInfo->szName, "Screen Saver");
			strcpy(pInfo->szPath, "€6");
			strcpy(pInfo->szOpt, "");
			pInfo->dwHotKey = MOD_CONTROL << 9 | MOD_ALT << 9 | 0x53; // VK_S
			break;

		case 10:
			strcpy(pInfo->szName, "Resolution++");
			strcpy(pInfo->szPath, "€7");
			pInfo->dwHotKey = MOD_CONTROL << 9 | 0xBB; // VK_ADD
			break;

		case 11:
			strcpy(pInfo->szName, "Resolution--");
			strcpy(pInfo->szPath, "€8");
			pInfo->dwHotKey = MOD_CONTROL << 9 | 0xBD; // VK_SUBTRACT 
			break;

		default: 
			return FALSE;
	}
	dwCount++;
	return TRUE;
}
BOOL GetAppPath(LPCTSTR szFileName, LPTSTR szPath)
{
	strcpy(szPath, IDS_APPPATHS);
	strcat(szPath, "\\");
	strcat(szPath, szFileName);
	
	DWORD dwcb=MAX_PATH, dwType;
	HKEY hKey;
	
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, KEY_READ, &hKey)
		&& ERROR_SUCCESS ==  RegQueryValueEx(hKey, 0, 0, &dwType, (LPBYTE)szPath, &dwcb))
		return TRUE;
		
	szPath[0] = 0;
	return FALSE;
}