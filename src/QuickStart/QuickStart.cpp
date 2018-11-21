// QuickStart.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "QuickStart.h"
#include "QuickStartDlg.h"

#include "htmlhelp.h" 

//#include "WelcomeDlg.h"
//#include "registerdlg.h"
//#include "serial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOL IsWebPage(LPCTSTR szURL)
{	
	return (strstr(szURL, "www.") || strstr(szURL, "://")); 
}
BOOL IsExecutable(LPCTSTR szPath)
{
	LPCTSTR szExt = strrchr(szPath, '.');			
	return ( szExt && (0 == stricmp("exe", szExt+1) || 0 == stricmp("com", szExt+1)) ); 
}



/////////////////////////////////////////////////////////////////////////////
// CQuickStartApp

BEGIN_MESSAGE_MAP(CQuickStartApp, CWinApp)
	//{{AFX_MSG_MAP(CQuickStartApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickStartApp construction

CQuickStartApp::CQuickStartApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQuickStartApp object

CQuickStartApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CQuickStartApp initialization

BOOL CQuickStartApp::InitInstance()
{	
//	CSerial serial;
//	int i = serial.GetTrialDaysLeft();

	// check whether QuickStart is already loaded (only one instance is allowed)
	m_hOneInstanceMutex = CreateMutex( NULL, TRUE, "SC_QuickStartI9");

	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{
		HWND hPrevWnd = ::FindWindow( NULL, IDS_APPTITLE);
		if (hPrevWnd)
		{
			ShowWindow(hPrevWnd, SW_SHOW);
			BringWindowToTop(hPrevWnd);
			SetForegroundWindow(hPrevWnd);	
		}
		else
			AfxMessageBox(IDS_ONEINSTANCE);
	}
	else
	{
		//Enable3dControls();			// Call this when using MFC in a shared DLL
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	
		SetDialogBkColor(RGB(255,255,255), RGB(0,0,0));

		// change .hlp extension of help file to .chm
		CString szHelp = m_pszHelpFilePath;
		szHelp.Replace(".HLP", ".chm");
		free ((void*)m_pszHelpFilePath);
		m_pszHelpFilePath = _tcsdup(szHelp);
	
//		if (ShowWelcome(i))
//		{
			CQuickStartDlg dlg;
			m_pMainWnd = &dlg;
			dlg.DoModal();
//		}
	}

	return FALSE;
}

int CQuickStartApp::ExitInstance() 
{
	// close the mutex
	if (m_hOneInstanceMutex)
		CloseHandle(m_hOneInstanceMutex);
	
	return CWinApp::ExitInstance();
}

void CQuickStartApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	HtmlHelp(NULL, m_pszHelpFilePath, HH_HELP_CONTEXT, 
		nCmd == HELP_CONTEXT ? dwData : 0);	
}

/*BOOL CQuickStartApp::ShowWelcome(int iDaysLeft)
{
	CWelcomeDlg wdlg(iDaysLeft);
	
	switch (wdlg.DoModal())
	{
		case ID_REGISTER :
		{
			CRegisterDlg dlg;
			if (dlg.DoModal() == IDOK)
				return TRUE;
			
			return ShowWelcome(iDaysLeft);
		}
		case IDOK :
			return TRUE;

		default :
			return FALSE;
	}
}
*/