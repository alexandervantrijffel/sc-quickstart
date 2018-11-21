// WelcomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "WelcomeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg dialog


CWelcomeDlg::CWelcomeDlg(int iDaysLeft, CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomeDlg::IDD, pParent), m_nTrialDaysLeft(iDaysLeft)
{
	//{{AFX_DATA_INIT(CWelcomeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}


void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDlg)
	DDX_Control(pDX, IDC_WEB_SUPPORT, m_WebSupport);
	DDX_Control(pDX, IDC_WEB_HOME, m_WebHome);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialog)
	//{{AFX_MSG_MAP(CWelcomeDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_REGISTER, OnRegister)
	ON_BN_CLICKED(ID_BUY, OnBuy)
	ON_BN_CLICKED(IDC_REGISTER, OnRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg message handlers

BOOL CWelcomeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_WebSupport.SetURL(IDS_WEB_SUPPORT);

	SetDefID(ID_REGISTER);
	GetDlgItem(ID_REGISTER)->SetFocus();
	GetDlgItem(ID_REGISTER)->UpdateWindow();

	CString szWelcome;
	if (m_nTrialDaysLeft == -1)
		EndDialog(IDOK);
	else if (m_nTrialDaysLeft == 0)
	{
		CString sz;
		sz.LoadString(IDS_TRIALEXPIRED_SHORT);
		SetDlgItemText(IDC_WELCOME_TITLE, sz);

		SetWindowText(sz);

		szWelcome.LoadString(IDS_TRIALEXPIRED);
		
		for (int i = IDC_WELCOME_TIMEOUT ; i <= IDC_WELCOME_TIMEOUT3 ; i++)
			GetDlgItem(i)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
	}
	else
	{
		szWelcome.LoadString(IDS_WELCOME);		

		char szDL[20];
		itoa(m_nTrialDaysLeft, szDL, 10);
		strcat(szDL, " days remaining");
	
		SetDlgItemText(IDC_WELCOME_DAYSLEFT, szDL);

		LOGFONT lf;
        GetFont()->GetLogFont(&lf);
        lf.lfWeight = FW_DEMIBOLD;
		        
        m_CounterFont.CreateFontIndirect(&lf);
        //SetFont(&m_Font);

		GetDlgItem(IDC_WELCOME_TIMEOUT)->SetFont(&m_CounterFont);
		SetFont(&m_CounterFont);
		m_nSecs = 0;
		SetTimer(0, 1000, NULL);
	}

	SetDlgItemText(IDC_WELCOME_MSG, szWelcome);
	
	SetWindowPos( &wndTopMost, 0, 0, 0, 0
		, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREPOSITION | SWP_NOSENDCHANGING);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWelcomeDlg::OnTimer(UINT nIDEvent) 
{
	if (m_nSecs==9)
	{
		KillTimer(0);
		EndDialog(IDOK);
	}
	
	char szNum[2] = "";
	SetDlgItemText(IDC_WELCOME_TIMEOUT, itoa(-(m_nSecs-9),szNum, 10));

	CDialog::OnTimer(nIDEvent);
	m_nSecs++;
}

void CWelcomeDlg::OnRegister() 
{
	EndDialog(ID_REGISTER);
}

void CWelcomeDlg::OnBuy() 
{	
	if (((HINSTANCE)32 > ShellExecute( 
		NULL, NULL, IDS_WEB_BUY, NULL, NULL, SW_SHOWNORMAL)))
		MessageBeep(0);
}
//H CWelcomeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//DEL {
//DEL 	COLORREF White= RGB(255,255,255);
//DEL 	HBRUSH hbr=0;
//DEL 
//DEL 	pDC->SetBkMode(TRANSPARENT);
//DEL 
//DEL 	if (nCtlColor == CTLCOLOR_BTN)
//DEL 	{
//DEL 		pDC->SetBkColor(White);
//DEL 		SetBkColor(pDC->GetSafeHdc(), White);
//DEL 	}
//DEL 	pDC->SetBkColor(White);
//DEL 
//DEL 	hbr = CreateSolidBrush(White);
//DEL 	
//DEL 
//DEL 	//HBITMAP bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BG));
//DEL 	//hbr = CreatePatternBrush(bmp);
//DEL 	
//DEL 	
//DEL 	return hbr;
//DEL }
