// QSo.cpp: implementation of the CQSo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "QSo.h"

#include "shretr.h"
#include "tasks.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT CQSo::m_nNextHotID=1; // hotid 0 is for Ctrl+F1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CQSo,CObject);

CQSo::CQSo()
{
	m_bActive	=FALSE;
	m_hIcon		=0;
	m_nID		=m_nNextHotID++;
	m_nType		=QSO_TYPE_NONE;
	m_dwHotKey	=0;	
}

CQSo::~CQSo()
{
	if (m_hIcon)
		DeleteObject(m_hIcon);
}

CQSo::CQSo(CQSo& p)
{
	if (this != &p)
	{
		m_bActive	= p.m_bActive;
		m_dwHotKey	= p.m_dwHotKey;
		m_hIcon		= p.m_hIcon;
		m_szPath	= p.m_szPath;
		m_szName	= p.m_szName;
		m_szOpt		= p.m_szOpt;
		m_nType		= p.m_nType;
		m_nID		= p.m_nID;
	}
}

CQSo& CQSo::operator=(CQSo& p)
{
	if (this != &p)
	{
		m_bActive	= p.m_bActive;
		m_dwHotKey	= p.m_dwHotKey;
		m_hIcon		= p.m_hIcon;
		m_szPath	= p.m_szPath;
		m_szName	= p.m_szName;
		m_szOpt		= p.m_szOpt;
		m_nType		= p.m_nType;
		m_nID		= p.m_nID;
	}	

	return *this;
}

void CQSo::Serialize(CArchive& ar)
{
	if (ar.IsStoring() )
	{
		ar << m_bActive;
		ar << m_dwHotKey;
		ar << m_szPath;
		ar << m_szName;
		ar << m_szOpt;
	}
	else
	{
		ar >> m_bActive;
		ar >> m_dwHotKey;
		ar >> m_szPath;
		ar >> m_szName;
		ar >> m_szOpt;
	}
}

BOOL CQSo::Enable(BOOL bEnable)
{
	if (m_bActive != bEnable && m_dwHotKey)
	{
		HWND hMainWnd = ::AfxGetMainWnd()->GetSafeHwnd();
		
		if (bEnable)
		{
			m_bActive = RegisterHotKey( hMainWnd
				, m_nID
				, m_dwHotKey>>9
				, m_dwHotKey & 0xFF);
			
			if (!m_bActive)
			{
				CString sz;
				sz.LoadString(IDS_HOTKEYINUSE);
				sz.Replace("%s", m_szName);
				
				AfxMessageBox(sz, MB_ICONEXCLAMATION);
			}
		}
		else if (m_nID != QSO_HOTKEY_NOTUSED)
			m_bActive = !UnregisterHotKey(hMainWnd, m_nID);
	}
	
	return m_bActive;
}

BOOL CQSo::Execute()
{
	BOOL bRet=TRUE;

	switch (m_nType)
	{
		case QSO_TYPE_PROGRAM :
		{
			// check if path contains environment strings
			char szExpPath[MAX_PATH]="";
			if (!ExpandEnvironmentStrings(m_szPath, szExpPath, MAX_PATH))
				strcpy(szExpPath, m_szPath);	// just in case

			bRet = CreateProc(NULL, szExpPath + m_szOpt);
			break;
		}

		case QSO_TYPE_DOC :
		case QSO_TYPE_FOLDER :
		{
			bRet = ((HINSTANCE)32 < ShellExecute( 
				NULL, m_szOpt, m_szPath, NULL, NULL, SW_SHOWNORMAL));
			break;
		}

		case QSO_TYPE_TASK :
		{
			CTasks tasks;
			tasks.Execute(m_szPath, m_szOpt);
			break;
		}
	
		default : 
			ASSERT(0);
	}

	return bRet;
}

BOOL CQSo::Create(PADDQSO_INFO pInfo)
{
	ASSERT(!m_bActive);

	m_szName	=pInfo->szName;
	m_szPath	=pInfo->szPath;
	m_szOpt		=pInfo->szOpt;
	m_dwHotKey  =pInfo->dwHotKey;

	GetType();
	return TRUE;
}

HICON CQSo::GetIcon()
{
	if (m_hIcon)
		DeleteObject(m_hIcon);

	switch (m_nType)
	{
		case QSO_TYPE_TASK:
		{
			CTasks tasks;
			m_hIcon = tasks.GetIcon(m_szPath);
			break;
		}
		case QSO_TYPE_FOLDER:
			m_hIcon = CSHRetr::GetFolderIcon();
			break;

		case QSO_TYPE_DOC:
			if (IsWebPage(m_szPath))
			{
				m_hIcon = CSHRetr::GetURLIcon();
				break;
			}


		default :
			m_hIcon = CSHRetr::GetIcon(m_szPath);

	}
	
	if (0 == m_hIcon)
		m_hIcon = CSHRetr::GetSpecialFolderIcon(CSIDL_COMMON_STARTUP);

	
	return m_hIcon;
}

UINT CQSo::GetType()
{
	// check for task
	if (m_szPath[0] == '€')
		m_nType = QSO_TYPE_TASK;
	else
	{
		
		DWORD dwFAttr = GetFileAttributes(m_szPath);

		// check for webpage
		if (IsWebPage(m_szPath))
			m_nType=QSO_TYPE_DOC;

		// check for folder
		else if ((dwFAttr & FILE_ATTRIBUTE_DIRECTORY) && dwFAttr != -1 )
			m_nType=QSO_TYPE_FOLDER;

		// check for executable
		else if ( IsExecutable(m_szPath) )
			m_nType=QSO_TYPE_PROGRAM;

		else //  must be a document
			m_nType=QSO_TYPE_DOC;
	}
	return m_nType;
}

BOOL CQSo::CreateProc(LPCTSTR szApp, LPCTSTR szCmdLine)
{
	STARTUPINFO si = {0};
	si.lpDesktop = "Winsta0\\Default";
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	BOOL bRet;
	
	if ( (bRet=CreateProcess(szApp, (LPTSTR)szCmdLine, NULL, NULL, FALSE, NULL
		, NULL, NULL, &si, &pi)))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	return bRet;
}
