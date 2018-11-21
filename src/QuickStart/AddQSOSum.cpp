// AddQSOSum.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOSum.h"

#include "kb.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOSum property page

IMPLEMENT_DYNCREATE(CAddQSOSum, CPropPTemplate)

CAddQSOSum::CAddQSOSum() 
	: CPropPTemplate(CAddQSOSum::IDD, 0, IDS_ADDQSO_SUM)
{
	//{{AFX_DATA_INIT(CAddQSOSum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSOSum::~CAddQSOSum()
{
}

void CAddQSOSum::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOSum)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAddQSOSum, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOSum)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOSum message handlers

BOOL CAddQSOSum::OnSetActive()
{
	CPropPTemplate::OnSetActive();

	CPropertySheetEx* pParent = (CPropertySheetEx*)GetParent();
	pParent->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	
	CString szType;
	switch (m_nType)
	{
		case IDD_ADDQSO_PROGRAM :
			szType = "Start a program";
			break;
		case IDD_ADDQSO_TASK :
			szType = "Start a task";
			break;
		case IDD_ADDQSO_FOLDER :
			szType = m_Info.szOpt[0]=='o' ? "Open a folder"	: "Explore a folder";
			break;
		case IDD_ADDQSO_DOC :
			szType = m_Info.szOpt[0]=='o' ? "Open a document": "Print a document";
			break;
		default :
			ASSERT(0);
	}

	CString szSum;
	szSum.Format("Name:\r\n%s\r\n\r\n", m_Info.szName);
	SetDlgItemText(IDC_ADDQSO_SUM_SUM, szSum);

	CKb kb;
	szSum.Format(
			"Type:\r\n%s\r\n\r\n\r\n" \
			"%s%s\r\n\r\n\r\n" \
			"HotKey:\r\n%s\r\n"
		, szType
		, (m_nType==IDD_ADDQSO_TASK) 
			? "Task:\r\n" + m_Tasks.GetTaskDesc(m_Tasks.GetTaskIndex(m_Info.szPath))
			: "Path:\r\n" + m_Info.szPath
		, (m_nType==IDD_ADDQSO_PROGRAM) ? m_Info.szOpt : ""
		, kb.GetText(m_Info.dwHotKey));

	SetDlgItemText(IDC_ADDQSO_SUM_SUM2, szSum);

	((CStatic*)GetDlgItem(IDC_ADDQSO_ICON))->SetIcon(m_hIcon);

	return TRUE;
}
