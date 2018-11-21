// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "RegisterDlg.h"

#include "serial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog


CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegisterDlg)
	m_szName = _T("");
	m_szRegNumber = _T("");
	//}}AFX_DATA_INIT
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterDlg)
	DDX_Text(pDX, IDC_NAME, m_szName);
	DDX_Text(pDX, IDC_REGNUMBER, m_szRegNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	//{{AFX_MSG_MAP(CRegisterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg message handlers

void CRegisterDlg::OnOK() 
{
	UpdateData();

	CSerial serial;
	m_szRegNumber.TrimRight(" ");
	if (serial.Register(m_szName, m_szRegNumber))
	{
		AfxMessageBox(IDS_SERIAL_ACCEPTED, MB_ICONINFORMATION);	
		CDialog::OnOK();
	}
	else
		AfxMessageBox(IDS_SERIAL_INVALID, MB_ICONEXCLAMATION);
}

BOOL CRegisterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	GetDlgItem(IDC_REGISTER_NAME)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
