// Tasks.cpp: implementation of the CTasks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "Tasks.h"

#include "shretr.h"
#include "videomode.h"

#include "mmsystem.h"
#include "atsecurity.h"
#include <wininet.h>	// internet functions

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//SHSTDAPI SHEmptyRecycleBin(
  //  HWND hwnd, 
//    LPCTSTR pszRootPath, 
    //DWORD dwFlags
//);		
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTasks::CTasks()
{
}

CTasks::~CTasks()
{

}
	// task type path is in the form of €1 or €2
int CTasks::GetTaskIndex(LPCTSTR szTask)
{
	return atoi(szTask+1);
}

BOOL CALLBACK CTasks::EnumDesktopWindowsProc(HWND hWnd, LPARAM lParam)
{
	if ( (::IsWindowVisible(hWnd) || ::IsIconic(hWnd))
		&& GetParent(hWnd) == 0
		&& ::GetDesktopWindow() != hWnd)
	{
		TCHAR szWndTitle[MAX_PATH]=_T("");
		GetWindowText(hWnd, szWndTitle, MAX_PATH);
		if (strcmp(szWndTitle, IDS_APPTITLE) && _tcslen(szWndTitle))
		{	
			// check for windows' program manager
			GetClassName(hWnd, szWndTitle, MAX_PATH);
			if (strcmp(szWndTitle, _T("Progman")))
				PostMessage( hWnd, WM_CLOSE, 0, 0L);
		}
	}
	 
	return TRUE;
}

void CTasks::Execute(LPCTSTR szTask, LPCTSTR szOpt)
{
	BOOL bOpenCD=FALSE;

	switch (GetTaskIndex(szTask))
	{
		case TASK_ID_SEM:
		{
		  
		    HINSTANCE result = ShellExecute(NULL, _T("open"), _T("mailto:"), NULL,NULL, SW_SHOWNORMAL);
			// If it failed, get the .htm regkey and lookup the program
			if ((UINT)result <= HINSTANCE_ERROR)
				AfxMessageBox(_T("Operation failed"), MB_ICONSTOP);
			break;
		}

		case TASK_ID_DIC:	
		//	InternetAutodial(INTERNET_AUTODIAL_FORCE_UNATTENDED, 0);
		//	InternetAutodial(INTERNET_AUTODIAL_FORCE_ONLINE , 0);
			InternetAttemptConnect(0);
			break;

		case TASK_ID_HIC :
		{
			DWORD dwFlags=0;
				
			if (!InternetGetConnectedState(&dwFlags, 0) 
				|| (dwFlags & INTERNET_CONNECTION_MODEM)  
				|| (dwFlags & INTERNET_CONNECTION_MODEM_BUSY) )
			{
				for (int i=0 ; i < 20 ; i++)	//****************** verbeteren!
				{
					if (TRUE == InternetHangUp(i, 0))
						TRACE1("disconnected at position %d\n", i);
				}
			}
			break;
		}
		
		case TASK_ID_SOL	:
		{
			UINT uFlags=0x10;	//	EWX_FORCEIFHUNG

			CATSecurity sec;
			sec.Privilege(TEXT("SeShutdownPrivilege"), TRUE);
				switch (szOpt[0])
			{
				case '0' :	uFlags |= 0x08 | EWX_SHUTDOWN;	// EWX_POWEROFF
					break;
				case '1' :	uFlags |= EWX_REBOOT;
					break;
				case '2' :	uFlags |= EWX_LOGOFF;
					break;
				default	 :
					ASSERT(0);
			}
			
			ExitWindowsEx( uFlags, 0 );
			break;
		}	

		case TASK_ID_ECD :
			bOpenCD=TRUE;

		case TASK_ID_CCD :
			::AfxGetMainWnd()->BeginWaitCursor();

			if (szOpt[0] != '€')
				OpenCloseCDDrive(szOpt[0], bOpenCD);
			else
			{
				CString sz = CSHRetr::GetAllCDDrives();
				for (int i=0 ; i<sz.GetLength() ; i++)
					OpenCloseCDDrive(sz[i], bOpenCD);
			}

			::AfxGetMainWnd()->EndWaitCursor();
			break;
		
		case TASK_ID_ERB :
		{
			HMODULE hMod = LoadLibrary("shell32.dll");
			if (hMod)
			{
				HRESULT (STDAPICALLTYPE *lpfnEmptyRecycleBin)(HWND, LPCTSTR, DWORD);
				lpfnEmptyRecycleBin = (HRESULT (STDAPICALLTYPE*)(HWND, LPCTSTR, DWORD))
						GetProcAddress(hMod, "SHEmptyRecycleBinA");

				HRESULT hr = E_INVALIDARG;
				if (lpfnEmptyRecycleBin)
				{
					hr = lpfnEmptyRecycleBin(NULL, NULL, NULL);
				}

				if (!SUCCEEDED(hr))
				{
					CString szErr;
					szErr.Format("Unable to empty recycle bin (%u)", hr);

					AfxMessageBox( szErr, MB_ICONINFORMATION);
				}
			
				FreeLibrary(hMod);
			}
			break;
		}
		case TASK_ID_CTP:
			CSHRetr::InvokeCmd(CSIDL_CONTROLS, szOpt);
			break;

		case TASK_ID_SSC:
			SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, 0, SPIF_SENDCHANGE);
			Sleep(500);
			PostMessage(GetDesktopWindow(), WM_SYSCOMMAND, SC_SCREENSAVE, 0L);
			break;		

		case TASK_ID_IDR:
		{
			CVideoMode vmode;
			if (!vmode.IncreaseDisplayResolutionPermanently())
				MessageBeep(0);			
			break;
		}
		case TASK_ID_DDR:
		{
			CVideoMode vmode;
			if (!vmode.DecreaseDisplayResolutionPermanently())
				MessageBeep(0);			
			break;
		}
		case TASK_ID_CAP:
			EnumDesktopWindows(NULL, CTasks::EnumDesktopWindowsProc, 0);
			break; 
			
		default :
			ASSERT(0);
	}
	
}

CString CTasks::GetTaskDesc(int iIndex)
{
	ASSERT(iIndex<m_szTasks.GetSize());
	Init();
	return m_szTasks[iIndex];
}

int CTasks::GetCount()
{
	Init();
	return m_szTasks.GetSize();
}

CString CTasks::GetTaskName(int iIndex)
{
	ASSERT(iIndex<m_szTasks.GetSize());

	CString sz;
	sz.Format("€%d", iIndex);
	return sz;
}


// Open or Close CD Drive
// cDrive is Drive Letter to Open, or 1 for 'Default' drive
void CTasks::OpenCloseCDDrive(TCHAR cDrive, BOOL bOpen)
{
	MCI_OPEN_PARMS op;
	MCI_STATUS_PARMS st;
	DWORD flags;

	TCHAR szDriveName[4];
	strcpy(szDriveName, "X:");

	::ZeroMemory(&op, sizeof(MCI_OPEN_PARMS));
	op.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;
	
	if(cDrive > 1)
	{
		szDriveName[0] = cDrive;
		op.lpstrElementName = szDriveName;
		flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE;
	}
	else flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE;

	if (!mciSendCommand(0,MCI_OPEN,flags,(unsigned long)&op)) 
	{
		st.dwItem = MCI_STATUS_READY;

		if(bOpen)
			mciSendCommand(op.wDeviceID,MCI_SET,MCI_SET_DOOR_OPEN,0);
		else
			mciSendCommand(op.wDeviceID,MCI_SET,MCI_SET_DOOR_CLOSED,0);

		mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,0);
	}
}

void CTasks::Init()
{
	// first time?
	if (!m_szTasks.GetSize())
	{
		m_szTasks.Add("Dial default internet connection");
		m_szTasks.Add("Hangup internet connection");
		m_szTasks.Add("Shutdown or logoff");
		m_szTasks.Add("Eject CD");
		m_szTasks.Add("Close CD");
		m_szTasks.Add("Show control panel");
		m_szTasks.Add(_T("Start Screensaver"));
		m_szTasks.Add(_T("Increase display resolution"));
		m_szTasks.Add(_T("Decrease display resolution"));
		m_szTasks.Add(_T("Close all programs"));
		m_szTasks.Add(_T("Send e-mail message"));


		// COM+ supported?
		OSVERSIONINFO vi;
		vi.dwOSVersionInfoSize=sizeof(vi);
		if (GetVersionEx(&vi) && vi.dwMajorVersion > 4)
		{	
			m_szTasks.Add("Empty recycle bin");
		}
	}

}

HICON CTasks::GetIcon(LPCTSTR szTask)
{	
	CSHRetr shretr;
	HICON hIcon=0;
	switch (GetTaskIndex(szTask))
	{
		case TASK_ID_DIC:
		case TASK_ID_HIC:
			hIcon = shretr.GetURLIcon();
			break;

		case TASK_ID_ECD:
		case TASK_ID_CCD:
			hIcon = shretr.GetCDIcon();
			break;

		case TASK_ID_SOL:
			hIcon = shretr.GetSpecialFolderIcon(CSIDL_DRIVES);
			break;

		case TASK_ID_CTP:
			hIcon = shretr.GetSpecialFolderIcon(CSIDL_CONTROLS);
			break;

		case TASK_ID_ERB:
			hIcon = shretr.GetSpecialFolderIcon(CSIDL_BITBUCKET);
			break;

		case TASK_ID_SSC:
		case TASK_ID_IDR:
		case TASK_ID_DDR:
			hIcon = LoadIcon(AfxGetInstanceHandle()
				, MAKEINTRESOURCE(IDI_DISPLAYSETTINGS));
			break;

		default:
			hIcon = LoadIcon(AfxGetInstanceHandle()
				, MAKEINTRESOURCE(IDI_TASK) );
	}

	return hIcon;
}