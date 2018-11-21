// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "ConfigDlg.h"

#include "settings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_CONFIG_REMOVEALLQS, OnRemoveAll)
	ON_BN_CLICKED(IDC_CONFIG_LOADDEFCFG, OnLoadDefCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CSettings set;
	
	GetDlgItem(IDC_AUTOSTART)->SendMessage(BM_SETCHECK
		, set.GetDW(IDS_SETTING_AUTOSTART), 0L);
	GetDlgItem(IDC_SHOWSTART)->SendMessage(BM_SETCHECK
		, set.GetDW(IDS_SETTING_SHOWSTART), 0L);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::OnOK() 
{
	CSettings set;

	BOOL bAStart = GetDlgItem(IDC_AUTOSTART)->SendMessage(BM_GETCHECK, 0, 0L);
	set.EnableAutoStart(bAStart);

	set.Set(IDS_SETTING_AUTOSTART, bAStart);
	
	set.Set(IDS_SETTING_SHOWSTART, GetDlgItem(IDC_SHOWSTART)->SendMessage(
		BM_GETCHECK, 0, 0L));
	
	
	CDialog::OnOK();
}

void CConfigDlg::OnRemoveAll() 
{
	if (IDYES == AfxMessageBox(IDS_REMOVEALL, MB_ICONQUESTION|MB_YESNO))
		GetParent()->SendMessage(WM_REMOVEALLQS, 0, 0L);
}

void CConfigDlg::OnLoadDefCfg() 
{
	int iRet = AfxMessageBox(IDS_LOADDEFCONFIG, MB_ICONQUESTION|MB_YESNOCANCEL|MB_DEFBUTTON2);

	if (iRet == IDYES)
		GetParent()->SendMessage(WM_LOADDEFCFG, 1, 0L);
	else if (iRet == IDNO)
		GetParent()->SendMessage(WM_LOADDEFCFG, 0, 0L);
}
