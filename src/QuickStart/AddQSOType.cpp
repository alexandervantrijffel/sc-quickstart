// AddQSOType.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOType property page

IMPLEMENT_DYNCREATE(CAddQSOType, CPropPTemplate)

CAddQSOType::CAddQSOType() 
	: CPropPTemplate(CAddQSOType::IDD, 0, IDS_ADDQSO_TYPE)
{
	//{{AFX_DATA_INIT(CAddQSOType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSOType::~CAddQSOType()
{
}

void CAddQSOType::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOType)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOType, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOType message handlers

BOOL CAddQSOType::OnSetActive()
{
	CPropPTemplate::OnSetActive();

	CPropertySheetEx* pSheet = (CPropertySheetEx*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_NEXT);

	if (m_bFirstT)
	{
		m_bFirstT = FALSE;
		SetCheck(IDC_ADDQSO_TYPE_PROGRAM);
	}

	return TRUE;
}

LRESULT CAddQSOType::OnWizardNext()
{
	UINT NextP=0;
	
	if (GetCheck(IDC_ADDQSO_TYPE_PROGRAM))
		NextP=IDD_ADDQSO_PROGRAM;
	else if (GetCheck(IDC_ADDQSO_TYPE_TASK))
		NextP=IDD_ADDQSO_TASK;
	else if (GetCheck(IDC_ADDQSO_TYPE_DOC))
		NextP=IDD_ADDQSO_DOC;
	else if (GetCheck(IDC_ADDQSO_TYPE_FOLDER))
		NextP=IDD_ADDQSO_FOLDER;
	else
		ASSERT(0);

	m_nType = NextP;
	return static_cast<LRESULT>(NextP);
}