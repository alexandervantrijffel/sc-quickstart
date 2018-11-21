// AddQSODoc.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSODoc.h"

#include "shretr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSODoc property page

IMPLEMENT_DYNCREATE(CAddQSODoc, CPropPTemplate)

CAddQSODoc::CAddQSODoc() 
	: CPropPTemplate(CAddQSODoc::IDD, 0, IDS_ADDQSO_DOC)
{
	//{{AFX_DATA_INIT(CAddQSODoc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSODoc::~CAddQSODoc()
{
}

void CAddQSODoc::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSODoc)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAddQSODoc, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSODoc)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSODoc message handler

BOOL CAddQSODoc::OnSetActive()
{
	CPropPTemplate::OnSetActive();

	SetBrowseBitmap();

	if (m_bFirstT)
	{
		m_bFirstT = FALSE;
		SetDlgItemText(IDC_ADDQSO_DOC_PATH, m_Info.szPath);

		if (!m_Info.szOpt.GetLength() || m_Info.szOpt == "open")
			SetCheck(IDC_ADDQSO_DOC_OPEN);
		else
			SetCheck(IDC_ADDQSO_DOC_PRINT);
	}
	return TRUE;
}

LRESULT CAddQSODoc::OnWizardNext()
{
	char szPath[MAX_PATH];
	if (!GetDlgItemText(IDC_ADDQSO_DOC_PATH, szPath, MAX_PATH)
		|| GetFileAttributes(szPath) == -1 && !IsWebPage(szPath))
	{
		AfxMessageBox(IDS_NODOCNAME, MB_ICONQUESTION);
		return -1;
	}

	SetTheIcon(CSHRetr::GetIcon(szPath) );

	if (GetCheck(IDC_ADDQSO_DOC_OPEN))
		m_Info.szOpt="open";
	else
		m_Info.szOpt="print";
	
	m_Info.szPath = szPath;

	return CPropPTemplate::OnWizardNext();
}

void CAddQSODoc::OnBrowse() 
{
	CFileDialog FDlg(TRUE
		, NULL 
		, NULL
		, OFN_FILEMUSTEXIST
		, "All files (*.*)|*.*||"
		, this);
	if (FDlg.DoModal() == IDOK)
		SetDlgItemText(IDC_ADDQSO_DOC_PATH,FDlg.GetPathName());	
}
