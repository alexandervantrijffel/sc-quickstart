// Tips.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "Tips.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTips dialog


CTips::CTips(UINT IDD, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CTips)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTips::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTips)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTips, CDialog)
	//{{AFX_MSG_MAP(CTips)
	ON_COMMAND(IDOK, OnOk)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDCANCEL, OnCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTips message handlers

void CTips::OnOk() 
{
	EndDlg();	
}

void CTips::OnCancel()
{
	EndDlg();
}

void CTips::EndDlg()
{
	if (GetDlgItem(IDC_TIP_SHOWAGAIN)->SendMessage(BM_GETCHECK, 0, 0L))
		EndDialog(IDCANCEL);
	else
		EndDialog(IDOK);
}
