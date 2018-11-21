// QuickStartDlg.cpp : implementation file
//

// ToDo:
/*
AUDIO CONTROL COMMANDS
 
 quiet  —  suppress the "Gibson sigh" Wizmo sound
Since Wizmo is usually not seen, it generates a soft sound to indicate its performance of a task. This sound may be suppressed by placing the "quiet" command early in Wizmo's command list.
Example: wizmo quiet desktop
 
 volume={0-100}  —  set the system's audio level
If you enjoy associating sounds with system events, you probably grow accustomed to the sounds being at a certain volume level. So, when you need to turn that volume up or down when playing a video clip, or being away from your machine, it is convenient to be able to return the volume to its original level. Wizmo's "volume=" command easily sets the system's volume to a percentage of full volume. Another use for this is creating simple script programs. The example below demonstrates a simple script to turn the volume up while the screen saver is active, then back down after blanking is cancelled.
Example: wizmo volume=90 monoff volume=20
 
 play={wavefile}  —  play the specified file
The "play=" verb gives you the flexibility to associate your own sounds and sound effects with your Wizmo shortcuts and command execution.
Example: wizmo play=c:\windows\media\chimes.wav
 
 wave={0-100}  —  set the system's wave file audio level
The system's wave file playback level can be controlled independently from the overall sound level. The "wave=" command allows this to be independently set.
Example: wizmo wave=25
 
 mute={0|1}  —  control the system's audio muting
The system's audio generation can be easily muted without changing any other level settings. This can be useful to keep the system quiet during screen blanking or while talking on the phone.
Example: wizmo mute=1 
*/
// CTasks::Execute() - case TASK_ID_CAP testen en activeren
//
//
// CTasks::Execute BOOL laten retourneren en CAddQSOTask::Test
// foutmelding laten geven wanneer CTasks::Execute faalt
// 
// accelerators voor information, hide en addqso werken niet
//
// PrintHotKeySummary()
//
// Aantal qs objects per pagina variabel maken
//
// /******************/ afmaken
//
// hotkeyregistratie netjes afhandelen als de hotkey in gebruik is
//
//

// Afgehandeld:
//
// R007: eind november 2002
// * SendMessage() - taak toevoegen
//
// R006: 31-10-02
// * hideonstartup werkt niet 

// R005:
// * prevented that "Omar" can register
// * added new tasks: 
//		* Start screensaver
//		* Increase/Decrease displayresolution
// * added CTipsMgr
//
// het uitvoeren van empty recycle bin veroorzaakt fouten (alleen in DEBUG mode)
//
// Nadat er een hotkey is ingevoerd en op ok is geklikt dient knop 'volgende'
// v/d wizard de focus te krijgen
//
// autostart regelen
// 
// het opstarten van meerdere SC-Quickstart instanties 
// voorkomen (ivm hotkey registratie)
//
// CQSo::GetType controleert nog niet op QSO_TYPE_TASK
// 
// Execute(UINT) en Execute(int) verfijnen (ambiguïteitsprobleem verhelpen)
//
// binnen open document URL's ondersteunen of daarvoor een aparte
// propertypage aanmaken
//
// F12 probleem bij het opnemen van een hotkey
//
// Move left,right,up,down implementeren


#include "stdafx.h"
#include "QuickStart.h"
#include "QuickStartDlg.h"

#include "addqso.h"
#include "settings.h"
#include "configdlg.h"

#include "tipsmgr.h"
#include "shretr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define QS_HOTKEY_SHOWDLG 0

//typedef BOOL (* PFNGETDEFCFG)(BOOL);
typedef BOOL (FAR PASCAL* PFNGETDEFCFG)(LPVOID);

#include "hyperlink.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink m_WebSupport;
	CHyperLink m_WebHome;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_WEB_SUPPORT, m_WebSupport);
	DDX_Control(pDX, IDC_WEB_HOME, m_WebHome);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickStartDlg dialog

CQuickStartDlg::CQuickStartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuickStartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuickStartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuickStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuickStartDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	for (int i=0;i<8;i++)
		DDX_Control(pDX, IDC_BUTTON1+i, m_QSBtn[i]);
	DDX_Control(pDX, IDC_UP, m_BtnUp);
	DDX_Control(pDX, IDC_DOWN, m_BtnDown);
	DDX_Control(pDX, IDC_CONFIG, m_StBtn[0]);
	DDX_Control(pDX, IDC_ADDQSO, m_StBtn[1]);
	DDX_Control(pDX, ID_HELP, m_StBtn[2]);
	DDX_Control(pDX, ID_HIDE, m_StBtn[3]);
}

BEGIN_MESSAGE_MAP(CQuickStartDlg, CDialog)
	//{{AFX_MSG_MAP(CQuickStartDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ADDQSO, OnAddQSO)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(ID_HIDE, OnHide)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CONFIG, OnConfig)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(IDM_SYSTRAY_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_MESSAGE(WM_CTCMD, OnCTCmd)
	ON_MESSAGE(WM_FILLSYSTRAYMENU, OnFillSysTrayMenu)
	ON_MESSAGE(WM_LOADDEFCFG, OnLoadDefConfig)
	ON_MESSAGE(WM_REMOVEALLQS, OnRemoveAll)
	ON_COMMAND_RANGE(IDM_SYSTRAY_FIRST,IDM_SYSTRAY_LAST, OnCmdSysTray)
	ON_COMMAND_RANGE(IDC_BUTTON1, IDC_LASTBUTTON, OnQSBtn)
	ON_COMMAND_RANGE(IDM_SYSMENUITEM1, IDM_SYSMENUITEMLAST, OnQSSysMenu)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickStartDlg message handlers


void CQuickStartDlg::InitializeBtn(CButtonST &btn)
{
	
	// Calculate a color effect for hilighting the button
	COLORREF Color = ::GetSysColor(COLOR_BTNFACE) + RGB(10, 20, 10);

	btn.SetColor(CButtonST::BTNST_COLOR_BK_IN,  Color);
	btn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(255,255,255));
	btn.SetBtnCursor(CSHRetr::GetHandCursor());
	btn.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn.DrawBorder(FALSE);

	btn.SetDrawTextFormat(DT_CENTER);
}

BOOL CQuickStartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
/*
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		// remove maximize command
		pSysMenu->RemoveMenu(4,MF_BYPOSITION);
	}
*/
	// Set the icon for this dialog.
	SetIcon(m_hIcon, FALSE);

	// initialize quickstart object buttons
	for (int i=0;i<8;i++)
	{	
		InitializeBtn(m_QSBtn[i]);
		m_QSBtn[i].Init();
	}
	
	m_nFirstDisplayedQS = 0;

	// initialize other buttons
	InitializeBtn(m_BtnUp);
	m_BtnUp.SetTooltipText("Scroll up  (PageUp)");
		
	InitializeBtn(m_BtnDown);
	m_BtnDown.SetTooltipText("Scroll down  (PageDn)");
	
	InitializeBtn(m_StBtn[0]);
	m_StBtn[0].SetTooltipText("Configure SC-QuickStart");
	m_StBtn[0].SetBitmaps(IDB_CONFIG, RGB(10,20,10));

	InitializeBtn(m_StBtn[1]);
	m_StBtn[1].SetTooltipText("Add QuickStart object  (+)");
	m_StBtn[1].SetBitmaps(IDB_ADDQSO, RGB(10,20,10));

	InitializeBtn(m_StBtn[2]);
	m_StBtn[2].SetTooltipText("Help  (F1)");
	m_StBtn[2].SetBitmaps(IDB_INFO, RGB(10,20,10));

	InitializeBtn(m_StBtn[3]);
	m_StBtn[3].SetTooltipText("Hide window  (CTRL+F1)");
	m_StBtn[3].SetBitmaps(IDB_CLOSE, RGB(10,20,10));

	// load quickstart objects from disk
	m_QSOArr.LoadObjects();
	UpdateAllQSBtn();

	// do not show icon on taskbar
	ModifyStyleEx(WS_EX_APPWINDOW, NULL);
	
	// systemtray
	m_SysTray.Create( NULL, WM_SYSTRAY_NOTIFY,IDS_APPTITLE,	
		::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME )),
										IDR_SYSTRAY);
	
	// systemtray popupmenu 
	m_SysTray.SetMenuDefaultItem(IDM_SYSTRAY_SHOW, FALSE);

	// load program settings from registry
	CSettings set;
	
	if (1 == set.GetDW(IDS_SETTING_AUTOSTART, 1))
		set.EnableAutoStart(TRUE);
	
	m_bShowStart = (1 == set.GetDW(IDS_SETTING_SHOWSTART, 1));
	
	// register SC-QuickStart's own hotkey
	RegisterHotKey( GetSafeHwnd(), QS_HOTKEY_SHOWDLG, MOD_CONTROL, VK_F1);
	
	m_hAccel = LoadAccelerators( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR) );

	// check whether this is the first time that the app is loaded after installation
	char szPath[MAX_PATH];
	if (GetModuleFileName(NULL, szPath, MAX_PATH))
	{	
		char* pszPath = strrchr(szPath, '\\');
		if (pszPath)
		{
			strcpy(pszPath+1, "ftime.dat");
			if (GetFileAttributes(szPath)!=-1)				
			{
				set.EnableAutoStart(TRUE);
				DeleteFile(szPath);

				if(!m_QSOArr.GetCount())
					SendMessage(WM_LOADDEFCFG, 0, 0L);
			}
		}
	}
	SetWindowText(IDS_APPTITLE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//DEL void CQuickStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
//DEL {
//DEL 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//DEL 	{
//DEL 		CAboutDlg dlgAbout;
//DEL 		dlgAbout.DoModal();
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		CDialog::OnSysCommand(nID, lParam);
//DEL 	}
//DEL }

void CQuickStartDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQuickStartDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQuickStartDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CQuickStartDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;
	if (nCtlColor==CTLCOLOR_DLG)
		hbr = CreateSolidBrush(RGB(255,255,255));
	else
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

afx_msg void CQuickStartDlg::OnHotKey(WPARAM idHotKey, LPARAM KeyData)
{
	if (idHotKey == QS_HOTKEY_SHOWDLG)
	{
		RECT rc;
		GetWindowRect(&rc);
		POINT pt = {rc.left, rc.top};

		// only hide if the window has the WS_VISIBLE style and
		// if the portion of the window at the upperleft coördinates 
		// is shown to the user
		if (  IsWindowVisible() && WindowFromPoint(pt)->GetSafeHwnd() == GetSafeHwnd())
			OnHide();
		else
			OnCmdSysTray(IDM_SYSTRAY_SHOW);
	}
	else
		m_QSOArr.ExecuteFromID(idHotKey);

}

void CQuickStartDlg::OnAddQSO() 
{
	CAddQSO aqso(IDS_ADDQSO, this);
	int iWizRet = aqso.DoModal();
	if ( 1 > iWizRet && aqso.m_psh.dwFlags & PSH_WIZARD97)
	{
		aqso.m_psh.dwFlags &= ~PSH_WIZARD97;
		aqso.m_psh.dwFlags |= PSH_WIZARD;
		iWizRet = aqso.DoModal();
	}

	if (iWizRet==ID_WIZFINISH)
	{
		int iPos = m_QSOArr.Add(aqso.GetInfo());
		ASSERT(iPos != -1);/*************/

		UpdateAllQSBtn();

		CTipsMgr tmgr;
		tmgr.ShowTip(ID_TIP_MODIFYQSO);
	}
}

void CQuickStartDlg::OnQSBtn(UINT ID)
{
	m_QSOArr.ExecuteFromPos(ID-IDC_BUTTON1+m_nFirstDisplayedQS);
}

void CQuickStartDlg::OnQSSysMenu(UINT nID)
{
	m_QSOArr.ExecuteFromPos(nID-IDM_SYSMENUITEM1);
}

// LOWORD(lQSID) == ID
// HIWORD(lQSID) == Enable

BOOL CQuickStartDlg::OnCTCmd(UINT nCmdID, long lQSID)
{
	BOOL bRet = TRUE;

	UINT nID = LOWORD(lQSID);
	int iDiff=0;

	switch (nCmdID)
	{	
		case IDM_CTMENU_MODIFY :
		{
			ADDQSO_INFO Info;
			m_QSOArr.GetInfo(LOWORD(lQSID), &Info);
			CAddQSO aqso(IDS_MODIFYQSO, &Info, m_QSOArr.GetType(LOWORD(lQSID)), this);

			int iWizRet = aqso.DoModal();
			if ( 1 > iWizRet && aqso.m_psh.dwFlags & PSH_WIZARD97)
			{
				aqso.m_psh.dwFlags &= ~PSH_WIZARD97;
				aqso.m_psh.dwFlags |= PSH_WIZARD;
				iWizRet = aqso.DoModal();
			}
	
			if (iWizRet==ID_WIZFINISH)
			{
				int iPos = m_QSOArr.Update(LOWORD(lQSID), aqso.GetInfo() );
				ASSERT(iPos != -1);/*************/

				UpdateAllQSBtn();
			}
			break;
		}

		case IDM_CTMENU_ENABLE :
			bRet=m_QSOArr.Enable(nID, HIWORD(lQSID));
			EnableQSBtn(m_QSOArr.GetObjectPos(nID)-m_nFirstDisplayedQS, bRet );
			break;
		
		case IDM_CTMENU_MOVE_LEFT :
	    	iDiff =-1;
		
		case IDM_CTMENU_MOVE_RIGHT :
			if (!iDiff)
				iDiff =1;

		case IDM_CTMENU_MOVE_UP	:
			if (!iDiff)
				iDiff =-4;

		case IDM_CTMENU_MOVE_DOWN :
			if (!iDiff)
				iDiff = 4;

		case IDM_CTMENU_MOVE_BEGIN :
			if (!iDiff)
				iDiff = FLIP_WITH_BEGIN;

		case IDM_CTMENU_MOVE_END :
			if (!iDiff)
				iDiff = FLIP_WITH_END;

			if (m_QSOArr.FlipQSO(nID, iDiff))
				UpdateAllQSBtn();
			else
				MessageBeep(0xFFFFFFFF);
			break;

		case IDM_CTMENU_REMOVE :
			if (IDYES == AfxMessageBox(IDS_SURE, MB_YESNO | MB_ICONQUESTION))
			{
				m_QSOArr.RemoveObject(LOWORD(lQSID));
				UpdateAllQSBtn();
			}
			break;

		default :
			ASSERT(0);
	}
	return bRet;
}

void CQuickStartDlg::UpdateAllQSBtn()
{
	UINT ic = m_QSOArr.GetCount();
		
	for (int i=0 ; i<8 && i+m_nFirstDisplayedQS < ic ; i++)
	{
		m_QSBtn[i].Update(
			  m_QSOArr.GetDisplayName(i+m_nFirstDisplayedQS)
			, m_QSOArr.GetHotKey(i+m_nFirstDisplayedQS)
			, m_QSOArr.GetIcon(i+m_nFirstDisplayedQS)
			, m_QSOArr.GetID(i+m_nFirstDisplayedQS)
			);
		
		EnableQSBtn(i, m_QSOArr.IsEnabled(i+m_nFirstDisplayedQS));
	}
	i--;

	// clear info for quickstart object buttons with no corresponding 
	// quickstart objects
	while (i++<7)
	{
		EnableQSBtn(i, FALSE);
		m_QSBtn[i].EnableWindow(FALSE);

		m_QSBtn[i].Update(
			  ""
			, ""
			, NULL
			, NULL);
	}

	BOOL bEn = m_QSOArr.GetCount() > (int)m_nFirstDisplayedQS+8;
	m_BtnDown.SetBitmaps(bEn ? IDB_DOWN : IDB_DOWNDIS, RGB(10,20,10));
	m_BtnDown.EnableWindow( bEn );
	

	bEn = m_nFirstDisplayedQS >= 8;
	m_BtnUp.SetBitmaps(bEn ? IDB_UP : IDB_UPDIS, RGB(10,20,10));
	m_BtnUp.EnableWindow( bEn );
	
}

void CQuickStartDlg::EnableQSBtn(int iPos, BOOL bEnable)
{	
	m_QSBtn[iPos].EnableIT(bEnable);
		
	m_QSBtn[iPos].EnableWindow(TRUE);	
	
	if(bEnable)
	{
		CString szPath;
		szPath.Format("%s  (%d)"
			, m_QSOArr.GetType( m_QSOArr.GetID(iPos+m_nFirstDisplayedQS) ) == QSO_TYPE_TASK 
				? m_QSOArr.GetDisplayName(iPos+m_nFirstDisplayedQS)
				: m_QSOArr.GetPath(iPos+m_nFirstDisplayedQS)
			, iPos+1);

		m_QSBtn[iPos].SetTooltipText(szPath);
	}
	else
		m_QSBtn[iPos].SetTooltipText("Hotkey disabled");
}

void CQuickStartDlg::OnFillSysTrayMenu(WPARAM w, LPARAM hMenu)
{
	HMENU hCurMenu = (HMENU)hMenu;
	
	MENUITEMINFO minfo={0};
	
	minfo.cbSize	= sizeof(minfo);
	minfo.fMask		= MIIM_TYPE | MIIM_STATE | MIIM_ID;
	minfo.fType		= MF_STRING;

	int ic = m_QSOArr.GetCount();
	for (int i=0 ; i<ic ; i++)
	{
		minfo.fState = m_QSOArr.IsEnabled(i) ? MFS_DEFAULT : MFS_GRAYED;
		minfo.wID = IDM_SYSMENUITEM1+i;
		CString szName = m_QSOArr.GetDisplayName(i);
		szName += "\t" + m_QSOArr.GetHotKey(i);
		minfo.dwTypeData = (LPTSTR)(LPCTSTR)szName;
		InsertMenuItem(hCurMenu, i, TRUE, &minfo);
	}
}

void CQuickStartDlg::OnDown() 
{
	if (m_BtnDown.IsWindowEnabled())	// could be executed by accelerator
	{
		m_nFirstDisplayedQS += 8;
		UpdateAllQSBtn();
	}

	SetFocus(); // for WM_MOUSEMOVE messages
}

void CQuickStartDlg::OnUp() 
{
	if (m_BtnUp.IsWindowEnabled())		// could be executed by accelerator
	{
		m_nFirstDisplayedQS -= 8;
		UpdateAllQSBtn();
	}

	SetFocus(); // for WM_MOUSEMOVE messages
}

void CQuickStartDlg::OnHide() 
{
	ShowWindow(SW_SHOWMINIMIZED);
	ShowWindow(SW_HIDE);
}

// prevent the application from exiting if the user presses the X at the topright
// of this main dialog
void CQuickStartDlg::OnClose() 
{
	// CDialog::OnClose();
	OnHide();
}

void CQuickStartDlg::OnConfig() 
{
	CConfigDlg dlg(this);
	dlg.DoModal();
}

BOOL CQuickStartDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) 
	{
		ASSERT(m_hAccel);
		return ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CQuickStartDlg::OnLoadDefConfig(WPARAM wReplace, LPARAM lParam)
{	
	HMODULE hDLL = LoadLibrary("DefCfg.dll");
	if (!hDLL)
		return;

	PFNGETDEFCFG lpfnGetFirstCfg = (PFNGETDEFCFG) GetProcAddress(hDLL, "?GetFirstCfg@@YGXPAX@Z");
		PFNGETDEFCFG lpfnGetNextCfg = (PFNGETDEFCFG) GetProcAddress(hDLL, "?GetNextCfg@@YGHPAX@Z");
	if (0 == lpfnGetFirstCfg || 0 == lpfnGetNextCfg)
	{
		AfxMessageBox(IDS_DEFCFGDLLNOTFOUND, MB_ICONSTOP);
		//TRACE1("lasterr= %d\n", GetLastError() );
		return;
	}

	if (wReplace)
		m_QSOArr.RemoveAll();

	ADDQSO_INFO Info;

	ADDQSO_INFOC InfoC;
	InfoC.dwHotKey=0;
	InfoC.szName = new char[MAX_PATH];
	InfoC.szOpt = new char[MAX_PATH];
	InfoC.szPath = new char[MAX_PATH];

	(*lpfnGetFirstCfg)((LPVOID)&InfoC);
	
	Info.dwHotKey	= InfoC.dwHotKey;
	Info.szName		= InfoC.szName;
	Info.szOpt		= InfoC.szOpt;
	Info.szPath		= InfoC.szPath;
	m_QSOArr.Add(&Info);
	
	while ( (*lpfnGetNextCfg)((LPVOID)&InfoC))
	{
		Info.dwHotKey	= InfoC.dwHotKey;
		Info.szName		= InfoC.szName;
		Info.szOpt		= InfoC.szOpt;
		Info.szPath		= InfoC.szPath;
		m_QSOArr.Add(&Info);
	}	

	FreeLibrary(hDLL);


	delete[] InfoC.szName;
	delete[] InfoC.szOpt;
	delete[] InfoC.szPath;

	UpdateAllQSBtn();
}

void CQuickStartDlg::OnRemoveAll(WPARAM wParam, LPARAM lParam)
{
	m_QSOArr.RemoveAll();
	UpdateAllQSBtn();
}

BOOL CQuickStartDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	HIWORD(zDelta) > 0 ? OnDown() : OnUp();
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CQuickStartDlg::OnCmdSysTray(UINT nID)
{
	switch (nID)
	{
		case IDM_SYSTRAY_SHOW :
			m_bShowStart=1;
			SetWindowPos(0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);

			ShowWindow(SW_SHOWNORMAL);
			BringWindowToTop();
			SetForegroundWindow();

			break;

		default:
			ASSERT(0);
	}

}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_WebSupport.SetURL(IDS_WEB_SUPPORT);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQuickStartDlg::OnAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	
}

void CQuickStartDlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
    if(!m_bShowStart)
        lpwndpos->flags &= ~SWP_SHOWWINDOW;

    CDialog::OnWindowPosChanging(lpwndpos);
}
