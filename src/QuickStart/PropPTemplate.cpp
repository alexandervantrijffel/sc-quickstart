// PropPTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"

#include "PropPTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HBITMAP CPropPTemplate::m_hBrowse=0;
HICON	CPropPTemplate::m_hIcon=0;
UINT	CPropPTemplate::m_nType=0;
BOOL	CPropPTemplate::m_bModify=FALSE;

CTasks		CPropPTemplate::m_Tasks;
ADDQSO_INFO CPropPTemplate::m_Info;

/////////////////////////////////////////////////////////////////////////////
// CPropPTemplate property page

IMPLEMENT_DYNAMIC(CPropPTemplate, CPropertyPageEx)

CPropPTemplate::CPropPTemplate( UINT nIDTemplate, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle)
	: CPropertyPageEx(nIDTemplate, nIDCaption, nIDHeaderTitle, nIDHeaderSubTitle )
{
	m_nID = nIDTemplate;
	m_bFirstT = TRUE;
}

CPropPTemplate::~CPropPTemplate()
{
}

BEGIN_MESSAGE_MAP(CPropPTemplate,CPropertyPageEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropPTemplate message handlers

LRESULT CPropPTemplate::GetCheck(UINT wID)
{
	return GetDlgItem(wID)->SendMessage(BM_GETCHECK, 0L, 0L);
}

LRESULT CPropPTemplate::SetCheck(UINT wID)
{
	return GetDlgItem(wID)->SendMessage(BM_SETCHECK, 1L, 0L);
}

void CPropPTemplate::SetBrowseBitmap()
{
	if (!m_hBrowse)
		m_hBrowse=LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BROWSE));

	((CButton*)GetDlgItem(IDC_BROWSE))->SetBitmap(m_hBrowse);
}

BOOL CPropPTemplate::OnSetActive()
{
	CPropertyPage::OnSetActive();

	CPropertySheetEx* pSheet = (CPropertySheetEx*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);

	return TRUE;
}

LRESULT CPropPTemplate::OnWizardBack()
{
	if (m_nID>=IDD_ADDQSO_PROGRAM && m_nID<=IDD_ADDQSO_DOC)
	{
		if (!m_bModify)
			return static_cast<LRESULT>(IDD_ADDQSO_TYPE);
		else
			return m_nID;
	}
	else if (m_nID == IDD_ADDQSO_HOTKEY)
		return m_nType;

	return 0;
}

LRESULT CPropPTemplate::OnWizardNext()
{
	if (m_nID>=IDD_ADDQSO_PROGRAM && m_nID<=IDD_ADDQSO_DOC)
		return static_cast<LRESULT>(IDD_ADDQSO_HOTKEY);
	return 0;
}

void CPropPTemplate::CleanUpGDI()
{
	if (m_hBrowse)
	{
		DeleteObject(m_hBrowse);
		m_hBrowse=0;
	}
	if (m_hIcon)
	{
		DeleteObject(m_hIcon);
		m_hIcon=0;
	}
}

void CPropPTemplate::SetTheIcon(HICON hIcon)
{
	if (m_hIcon)
		DeleteObject(m_hIcon);
				
	if (hIcon==(HICON)1) // not a valid EXE or DLL?
		m_hIcon=0;
	else
		m_hIcon = hIcon;
}

const PADDQSO_INFO CPropPTemplate::GetInfo()
{
	return static_cast<const PADDQSO_INFO>(&m_Info);
}

HBRUSH CPropPTemplate::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	return CreateSolidBrush(RGB(255,255,255));
}
