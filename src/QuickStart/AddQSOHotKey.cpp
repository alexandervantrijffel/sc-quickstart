// AddQSOHotKey.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOHotKey.h"

#include "AddQSOHotKeyRecord.h"
#include "kb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOHotKey property page

IMPLEMENT_DYNCREATE(CAddQSOHotKey, CPropPTemplate)

CAddQSOHotKey::CAddQSOHotKey() : 
	CPropPTemplate(CAddQSOHotKey::IDD, 0, IDS_ADDQSO_HOTKEY)
{
	//{{AFX_DATA_INIT(CAddQSOHotKey)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSOHotKey::~CAddQSOHotKey()
{
}

void CAddQSOHotKey::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOHotKey)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOHotKey, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOHotKey)
	ON_BN_CLICKED(IDC_ADDQSO_HOTKEY_RECORD, OnRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOHotKey message handlers
BOOL CAddQSOHotKey::OnSetActive()
{
	CPropPTemplate::OnSetActive();
	
	if (m_bFirstT)
	{
		m_bFirstT = FALSE;
		CKb kb;
		SetDlgItemText(IDC_ADDQSO_HOTKEY_HOTKEY, kb.GetText(m_Info.dwHotKey));
	}
	return TRUE;
}

void CAddQSOHotKey::OnRecord() 
{
	CAddQSOHotKeyRecord rec(this);
	if (rec.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_ADDQSO_HOTKEY_HOTKEY, rec.GetHotKeyText() );
		m_Info.dwHotKey = rec.GetHotKey();

		CWnd* pParent = GetParent();
		int iID = ((CPropertyPageEx*)pParent)->GetDefID();
		if (iID)
		{
			CWnd* pBtn = pParent->GetDlgItem(LOWORD(iID));
			
			if (pBtn)
				pBtn->SetFocus();
		}
	}
}
