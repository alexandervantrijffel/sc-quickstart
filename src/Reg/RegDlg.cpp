// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Reg.h"
#include "RegDlg.h"

#include "../quickstart/crc.h"
//#include "../../../ATKit/ATFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

BOOL CRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegDlg::OnPaint() 
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
HCURSOR CRegDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CString CRegDlg::GetRegistrationNumber(CString szName)
{
	try
	{
		if (szName.IsEmpty())
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

		CString szRefSerial;
		szRefSerial.Format("%u-%u-%u-%u", dwSer[0], dwSer[1] ^ dwSer[2] , dwSer[2], dwSer[1]);
		return szRefSerial;
/*		TRACE1("should be %s\n", szRefSerial);

		if (0 == szRefSerial.Compare(szSerial))
		{
			szRefSerial += ":" + szName;
			CSettings set;
			set.Set("rdata", (LPBYTE)(LPCTSTR)szRefSerial, szRefSerial.GetLength());
			return TRUE;
		}
		*/
	}
	catch (...)
	{
		
	}
	
	return "";
}


void CRegDlg::OnOK() 
{
	CString szName;
	if (!GetDlgItemText(IDC_USERNAME, szName))
		MessageBeep(0);
	else
	{
		SetDlgItemText(IDC_REGNUMBER, GetRegistrationNumber(szName));
	}
	//CDialog::OnOK();
}
