// QuickStart.h : main header file for the QUICKSTART application
//

#if !defined(AFX_QUICKSTART_H__195B8715_52A6_4AA0_BF03_EA4457375ABD__INCLUDED_)
#define AFX_QUICKSTART_H__195B8715_52A6_4AA0_BF03_EA4457375ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define SCQ_MOD_CTRL	MOD_CONTROL<<9//17
#define SCQ_MOD_ALT		MOD_ALT<<9	//18
#define SCQ_MOD_SHIFT	MOD_SHIFT<<9//16
#define SCQ_MOD_WIN		MOD_WIN<<9//91

#define IDS_SETTINGS_NOTIPS "NoMsgs"

#define SCQ_MAXDISPLAYCHARS 22

#define WM_CTCMD			WM_APP+1
#define WM_SYSTRAY_NOTIFY	WM_APP+2
#define WM_FILLSYSTRAYMENU	WM_APP+3
#define WM_LOADDEFCFG		WM_APP+4
#define WM_REMOVEALLQS		WM_APP+5

#define IDS_SETTING_AUTOSTART	"AutoStart"
#define IDS_SETTING_SHOWSTART	"ShowOnStartUp"

#define IDS_NOHOTKEY			"No Hotkey"

//#define IDS_WEB_BUY				"http://www.soft-central.net/buy.php"
#define IDS_WEB_HOME			"http://www.soft-central.net"
#define IDS_WEB_SUPPORT			"mailto:support@soft-central.net"

#define IDS_APPTITLE			_T("SC-QuickStart")

BOOL IsWebPage(LPCTSTR szURL); 
BOOL IsExecutable(LPCTSTR szPath);

/////////////////////////////////////////////////////////////////////////////
// CQuickStartApp:
// See QuickStart.cpp for the implementation of this class
//

class CQuickStartApp : public CWinApp
{
public:
	CQuickStartApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickStartApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

protected:
	HANDLE m_hOneInstanceMutex;
//	BOOL	ShowWelcome(int iDaysLeft);
// Implementation

	//{{AFX_MSG(CQuickStartApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICKSTART_H__195B8715_52A6_4AA0_BF03_EA4457375ABD__INCLUDED_)
