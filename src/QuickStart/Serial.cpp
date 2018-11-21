// Serial.cpp: implementation of the CSerial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "Serial.h"
#include "settings.h"
#include "ATReg.h"
#include "crc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerial::CSerial()
{
	char szPath[MAX_PATH]="";
	GetSystemDirectory(szPath, MAX_PATH);
	strcat(szPath, "\\KBD7DAC.DRV");
	m_szFilePath = szPath;

	m_szRegPath1 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer";
	m_szRegVal1  = "MMCfgData";

	m_szRegPath2 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\H5921VNC";
	m_szRegVal2  = "Cnt";

	m_nMaxTrialDays = 30;
}

CSerial::~CSerial()
{

}

// function gettrialdaysleft
// returns 0 if trial has expired, a negative number if the software has been
// serialized

int CSerial::GetTrialDaysLeft()
{
	int iRet = 0;
/*
	// get crc
	char szModFile[MAX_PATH];
	DWORD dwRet = GetModuleFileName(NULL, szModFile, MAX_PATH);
	if (dwRet != NO_ERROR)
	{
		CCrc* pcrc = new CCrc;
		DWORD dwCrc=0;

		pcrc->Init();
		dwRet = pcrc->FileCrcAsm(szModFile, dwCrc);
		if (dwRet == NO_ERROR)
		{
			CString sz;
			sz.Format("Crc = %u", dwCrc);
			if (CRC != CRCSET)
				return 0;
			AfxMessageBox(sz);
		}
		pcrc->Free();
		delete pcrc;
	}
*/
	char* pszReg = new char[1024];
	CSettings set;
	DWORD dwcb=1024;
	if (set.GetB("rdata", (LPBYTE)pszReg, &dwcb)!= -1)
	{
		pszReg[dwcb / sizeof(char)]=0;
		CString szName = strstr(pszReg, ":")+1;
		LPTSTR psz = strstr(pszReg, ":");
		if (psz)
		{
			*psz = 0;
			if (Register(szName, pszReg))
			{
				delete[] pszReg;
				return -1;
			}
		}
	}

	delete[] pszReg;

	
	// 0 = file
	// 1 = reg1
	// 2 = reg2
	// 3 = current

	SYSTEMTIME ST[4];
	GetSystemTime(&ST[3]);

	CFile File;
 	if (!File.Open(m_szFilePath, CFile::modeRead)
		|| !File.Read(&ST[0],sizeof(ST[0])))
		ZeroMemory(&ST[0],sizeof(ST[0]));
	
	CATReg reg;
	dwcb = sizeof(ST[1]);
	if (ERROR_SUCCESS != reg.RegGetVal(HKEY_LOCAL_MACHINE
		, m_szRegPath1, m_szRegVal1, (LPTSTR)&ST[1], &dwcb))
		ZeroMemory(&ST[1],sizeof(ST[1]));

	dwcb = sizeof(ST[2]);
	if (ERROR_SUCCESS != reg.RegGetVal(HKEY_LOCAL_MACHINE
		, m_szRegPath2, m_szRegVal2, (LPTSTR)&ST[2], &dwcb))
		ZeroMemory(&ST[2],sizeof(ST[2]));
	
	// loop once to get a correct installed systemtime
	LPSYSTEMTIME lpSTCorrect=0;
	for (int i=0; i<3; i++)
	{
		if (IsValid(&ST[i]))
		{
			lpSTCorrect=&ST[i];
			break;
		}
	}

	// if no time value was found this must be the first time that
	// this app was executed
	if (0 == lpSTCorrect)
	{
		for ( i=0; i<3; i++)
			SetData(&ST[3], i);

		iRet = m_nMaxTrialDays;
	}
	else
	{

		// loop again to set data for invalid timevalues
		for (i=0; i<3; i++)
		{
			if (!IsValid(&ST[i]))
				SetData(lpSTCorrect, i);
		}
	
		// calculate days left
		CTime TimeInstalled(*lpSTCorrect),TimeCur(ST[3]);
		CTimeSpan ts = TimeCur - TimeInstalled;
		
		if (ts.GetDays() > m_nMaxTrialDays || ts.GetSeconds() < 0)
			iRet = 0;
		else
			iRet = m_nMaxTrialDays - ts.GetDays();
	}

	return iRet;
}


void CSerial::SetData(LPSYSTEMTIME lpST, int iIndex)
{
	if (iIndex == SERIAL_FILE)
	{
		CFile File;
		if (File.Open(m_szFilePath, CFile::modeCreate|CFile::modeWrite))
			File.Write(lpST, sizeof(*lpST));
	}
	
	HKEY hKey=0;
	CATReg reg;
	
	if (iIndex == SERIAL_REG1)
	{
		if (ERROR_SUCCESS == reg.RegCreateFullKeyPath(HKEY_LOCAL_MACHINE
			, m_szRegPath1, KEY_WRITE, &hKey))
			RegSetValueEx(hKey, m_szRegVal1, 0

				, REG_BINARY, (LPBYTE)lpST, sizeof(*lpST));
	}

	if (iIndex == SERIAL_REG2)
	{
		if (ERROR_SUCCESS == reg.RegCreateFullKeyPath(HKEY_LOCAL_MACHINE
			, m_szRegPath2, KEY_WRITE, &hKey))
		
			RegSetValueEx(hKey, m_szRegVal2, 0
				, REG_BINARY, (LPBYTE)lpST, sizeof(*lpST));
	}
}

BOOL CSerial::IsValid(LPSYSTEMTIME lpST)
{
	return (lpST != NULL && lpST->wYear >= 1980 && lpST->wDay <= 35
		&& lpST->wHour <= 26 && lpST->wMonth <= 14);
}

BOOL CSerial::Register(CString szName, CString szSerial)
{
	try
	{
		if (szName.IsEmpty() || szSerial.IsEmpty() || 0 == szName.CompareNoCase(_T("Omar")))
			throw 0;
	
		DWORD dwSer[3];
		CCrc crc;
		crc.Init();

		if (NO_ERROR != crc.StringCrc(szName, dwSer[1]))
			throw 0;
		CString szTmp = szName;

		char cReplace='f',cReplaceWith='a';
		int i=0;
		while (szTmp.Replace(cReplace++, cReplaceWith++) < 4 && i++ < 20);
			
		char* pszRev = new char[szTmp.GetLength()+1];

		strcpy(pszRev, szTmp);
					
		if (NO_ERROR != crc.StringCrc(strrev(pszRev), dwSer[0]))
		{
			delete[] pszRev;
			throw 0;
		}

		
		if (NO_ERROR != crc.StringCrc(strupr(pszRev), dwSer[2]))
		{
			delete[] pszRev;
			throw 0;
		}
		
		delete pszRev;

		TCHAR szRefSerial[2*MAX_PATH];
		DWORD dwSerFinal[4] = { dwSer[0], dwSer[1] ^ dwSer[2] , dwSer[2], dwSer[1] };
		int ic=0;
		for ( i=0 ; i< 4 ; i++ )
		{
			ultoa(dwSerFinal[i], szRefSerial, 10);
			if (strcmp(szRefSerial, szSerial.Mid(ic, strlen(szRefSerial))))
				throw(0);
			ic += strlen(szRefSerial)+1;
		}

		
//		TRACE1("should be %s\n", szRefSerial);

//		if (0 == szRefSerial.Compare(szSerial))
//		{
			LPTSTR pszName = szName.GetBuffer(MAX_PATH);
			if (!stricmp(strrev(pszName), _T("ramO")))
				throw(0);
			strrev(pszName);
			szName.ReleaseBuffer(-1);

			CSettings set;
			sprintf(szRefSerial,_T("%u-%u-%u-%u:%s"), dwSerFinal[0], dwSerFinal[1], dwSerFinal[2], dwSerFinal[3], szName);
			set.Set("rdata", (LPBYTE)(LPCTSTR)szRefSerial, strlen(szRefSerial));
			return TRUE;
//		}
	}
	catch (...)
	{
		
	}
	
	return FALSE;
}