// AddQSOName.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOName property page

IMPLEMENT_DYNCREATE(CAddQSOName, CPropPTemplate)

CAddQSOName::CAddQSOName() 
	: CPropPTemplate(CAddQSOName::IDD, 0, IDS_ADDQSO_NAME)
{
	//{{AFX_DATA_INIT(CAddQSOName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSOName::~CAddQSOName()
{
}

void CAddQSOName::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOName, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOName message handlers
BOOL CAddQSOName::OnSetActive()
{
	CPropPTemplate::OnSetActive();
	
	// name can change after we came here
	SetDlgItemText(IDC_ADDQSO_NAME_NAME, m_Info.szName);
	
	return TRUE;
}
LRESULT CAddQSOName::OnWizardNext()
{
	if (!GetDlgItemText(IDC_ADDQSO_NAME_NAME, m_Info.szName))
	{
		AfxMessageBox(IDS_NONAME, MB_ICONEXCLAMATION);
		return -1;
	}
	m_Info.szName.TrimRight(" ");
	return CPropPTemplate::OnWizardNext();
}

