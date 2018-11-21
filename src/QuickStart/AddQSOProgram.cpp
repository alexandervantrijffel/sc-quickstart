// AddQSOProgram.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOProgram.h"

#include "selectprogramdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOProgram property page

IMPLEMENT_DYNCREATE(CAddQSOProgram, CPropPTemplate)

CAddQSOProgram::CAddQSOProgram() 
	: CPropPTemplate(CAddQSOProgram::IDD, 0, IDS_ADDQSO_PROGRAM)
{
	//{{AFX_DATA_INIT(CAddQSOProgram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSOProgram::~CAddQSOProgram()
{
}

void CAddQSOProgram::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOProgram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOProgram, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOProgram)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_UPDATE(IDC_ADDQSO_PROGRAM_PATH, OnUpdatePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOProgram message handlers

BOOL CAddQSOProgram::OnSetActive()
{
	CPropPTemplate::OnSetActive();
	
	if (m_bFirstT)
	{
		m_bFirstT = FALSE;

		SetBrowseBitmap();

		SetDlgItemText(IDC_ADDQSO_PROGRAM_PATH, m_Info.szPath);
		SetDlgItemText(IDC_ADDQSO_PROGRAM_ARGUMENTS, m_Info.szOpt);

		if (!m_Info.szPath.GetLength())
			OnBrowse();
	}
	
	return TRUE;
}

void CAddQSOProgram::OnBrowse() 
{
	CSelectProgramDlg Dlg;
	if (Dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_ADDQSO_PROGRAM_PATH,Dlg.GetPathName());
}

LRESULT CAddQSOProgram::OnWizardNext()
{
	char szFile[MAX_PATH]="";
	GetDlgItemText(IDC_ADDQSO_PROGRAM_PATH,szFile, MAX_PATH);

	// trim spaces
	LPTSTR szEnd=szFile+strlen(szFile)-1;
	while(*szEnd == ' ')
		*szEnd-- = 0;

	if (!IsExecutable(szFile))
	{
		AfxMessageBox( IDS_NOEXECFILENAME, MB_ICONEXCLAMATION);
		return -1;
	}
	
	if (GetFileAttributes(szFile) == -1)
	{
		char szFileII[MAX_PATH]="";
		
		// check for environment strings (%s)
		if ( !strstr(szFile, "%")
			|| !ExpandEnvironmentStrings(szFile,szFileII,MAX_PATH)
			|| GetFileAttributes(szFileII) == -1)
		{
			AfxMessageBox( IDS_FILENOTFOUND, MB_ICONEXCLAMATION);
			return -1;
		}
	}

	m_Info.szPath = szFile;
	
	if (GetDlgItemText(IDC_ADDQSO_PROGRAM_ARGUMENTS, szFile, MAX_PATH))
	{
		// insert space if needed
		m_Info.szOpt = (szFile[0] != ' ')?" ":"";
		m_Info.szOpt += szFile;
	}
	else
		m_Info.szOpt= "";

	return CPropPTemplate::OnWizardNext();
}

void CAddQSOProgram::OnUpdatePath() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropPTemplate::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	char szFile[MAX_PATH]="";
	if (GetDlgItemText(IDC_ADDQSO_PROGRAM_PATH, szFile, MAX_PATH)
		&& IsExecutable(szFile))
	{
		SetTheIcon( ExtractIcon(::AfxGetInstanceHandle(), szFile, 0));
		
		((CStatic*)GetDlgItem(IDC_ADDQSO_ICON))->SetIcon(m_hIcon);
	}
}
