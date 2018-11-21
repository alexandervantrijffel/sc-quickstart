// QSBtn.cpp: implementation of the CQSBtn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "QSBtn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFont CQSBtn::m_TitleFont;
CFont CQSBtn::m_ShortFont;


BEGIN_MESSAGE_MAP(CQSBtn, CButtonST)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND_RANGE(IDM_CTMENU_MODIFY, IDM_CTMENU_REMOVE, OnCTCmd)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*		0,0,0, FW_MEDIUM, TRUE,TRUE,0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman ");
*/	

CQSBtn::CQSBtn()
{
	m_bEnabled=TRUE;
	if (!m_TitleFont.m_hObject)
	{
		m_ShortFont.CreateFont(14,
							0,0,0,
							FW_NORMAL,
							0,0,0,
							DEFAULT_CHARSET,
							OUT_CHARACTER_PRECIS,
							CLIP_CHARACTER_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							"Courier New");
		
		m_TitleFont.CreateFont(0,
							0,0,0,
							FW_MEDIUM,
							TRUE,TRUE,0,
							DEFAULT_CHARSET,
							OUT_CHARACTER_PRECIS,
							CLIP_CHARACTER_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							"Times New Roman");
	}
}
	

CQSBtn::~CQSBtn()
{
	if (m_TitleFont.m_hObject)
	{
		m_TitleFont.DeleteObject();
		m_ShortFont.DeleteObject();
	}
}

void CQSBtn::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	if (!m_bEnabled)
		lpDIS->itemState |= ODS_DISABLED;

	// preserve properties
	HICON hOrgIcon = m_csIcons[0].hIcon;
	int iOrgBottom = lpDIS->rcItem.bottom;
	COLORREF OrgColor = GetBkColor(lpDIS->hDC);
	HGDIOBJ hOldFont = SelectObject(lpDIS->hDC, m_TitleFont);

	// show disabled window
	//lpDIS->itemState |= ODS_DISABLED;

	// draw the title
	m_csIcons[0].hIcon=0;
	lpDIS->rcItem.bottom = 20;
	// set bgcolor to SC's blue color
	SetBkColor(lpDIS->hDC, RGB(25,25,145));
	CButtonST::DrawItem(lpDIS);
	
	// draw the shortkey
	m_pszWndText = &m_szShortKey;
	// reset original properties
	m_csIcons[0].hIcon = hOrgIcon;
	lpDIS->rcItem.bottom = iOrgBottom;
	lpDIS->rcItem.top = 20;
	SetBkColor(lpDIS->hDC, OrgColor);
	SelectObject(lpDIS->hDC, hOldFont);

	CButtonST::DrawItem(lpDIS);
	m_pszWndText=0;
}

void CQSBtn::OnRButtonDown(UINT nFlags, CPoint point)
{
	CButtonST::OnRButtonDown(nFlags, point);

	CMenu Menu, *pSubMenu;
	if (Menu.LoadMenu(IDR_CTMENU) 
		&& (pSubMenu = Menu.GetSubMenu(0)) )
	{

		if (m_szShortKey != IDS_NOHOTKEY)
		{
			pSubMenu->InsertMenu( 1, MF_BYPOSITION | MF_STRING, IDM_CTMENU_ENABLE
				, (m_bEnabled) ? "&Disable" : "&Enable");
		}
		
		POINT pt;
		GetCursorPos(&pt);

		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
	
		// send WM_KILLFOcUS to parent class to make sure that the background color 
		// of the button corresponds to the mouse  position ( white if mouse is out of rect, 
		// gray if the mouse is over this butten)

		SendMessage(WM_KILLFOCUS, 0, 0L);	
	}	
}

void CQSBtn::Update(CString szName, CString szHotKey, HICON hIcon, UINT nID)
{
	SetTooltipText(szName);
	m_nID = nID;
	SetWindowText(szName);
	m_szShortKey=szHotKey;
	SetIcon(hIcon);

}

UINT CQSBtn::GetID()
{
	return m_nID;
}

void CQSBtn::Init()
{
	SetFont(&m_ShortFont);
}

void CQSBtn::OnCTCmd(UINT nID)
{
	if (nID==IDM_CTMENU_ENABLE)
		m_bEnabled ^= 1;
	
	// sendmessage returns the state of the object
	m_bEnabled = GetParent()->SendMessage(WM_CTCMD, nID, static_cast<long>(m_nID | (m_bEnabled << 16)));
}

void CQSBtn::EnableIT(BOOL bEnable)
{
 	m_bEnabled=bEnable;
	RedrawWindow();
//	if (bEnable)
//		EnableWindow(TRUE);
	
	
}
