// AddQSO.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSO

IMPLEMENT_DYNAMIC(CAddQSO, CPropertySheetEx)

CAddQSO::CAddQSO(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark, HBITMAP hbmHeader)
	:CPropertySheetEx(nIDCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
	AddPage(&m_Type);
	AddPage(&m_Program);
	AddPage(&m_Task);
	AddPage(&m_Doc);
	AddPage(&m_Folder);
	AddPage(&m_HotKey);
	AddPage(&m_Name);
	AddPage(&m_Sum);
	
	m_Type.m_Info.szName="";
	m_Type.m_Info.szPath="";
	m_Type.m_Info.szOpt="";
	m_Type.m_Info.dwHotKey=0;

	m_psh.dwFlags |= PSH_WIZARD97;

	m_Type.m_bModify		= FALSE;
}

// for modifying object
CAddQSO::CAddQSO(UINT nIDCaption, PADDQSO_INFO pInfo, UINT nType, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark, HBITMAP hbmHeader)
	:CPropertySheetEx(nIDCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
	switch (nType)
	{
		case IDD_ADDQSO_PROGRAM	:	AddPage(&m_Program);
			break;
		case IDD_ADDQSO_TASK	:	AddPage(&m_Task);
			break;
		case IDD_ADDQSO_DOC		:	AddPage(&m_Doc);
			break;
		case IDD_ADDQSO_FOLDER	:	AddPage(&m_Folder);
			break;
	}
	AddPage(&m_HotKey);
	AddPage(&m_Name);
	AddPage(&m_Sum);

	m_psh.dwFlags |= PSH_WIZARD97;

	m_Type.m_Info.dwHotKey	= pInfo->dwHotKey;
	m_Type.m_Info.szName	= pInfo->szName;
	m_Type.m_Info.szOpt		= pInfo->szOpt;
	m_Type.m_Info.szPath	= pInfo->szPath;

	m_Type.m_bModify		= TRUE;
	m_Type.m_nType			= nType;
}

CAddQSO::~CAddQSO()
{
	m_Sum.CleanUpGDI();
}


BEGIN_MESSAGE_MAP(CAddQSO, CPropertySheetEx)
	//{{AFX_MSG_MAP(CAddQSO)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSO message handlers

const PADDQSO_INFO CAddQSO::GetInfo()
{
	return m_Type.GetInfo();
}



HBRUSH CAddQSO::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	return CreateSolidBrush(RGB(255,255,255));
}
