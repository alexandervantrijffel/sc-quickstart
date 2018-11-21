// SysTrayQS.cpp: implementation of the CSysTrayQS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "SysTrayQS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CSysTrayQS, CSystemTray);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysTrayQS::CSysTrayQS()
{

}

CSysTrayQS::~CSysTrayQS()
{

}

BOOL CSysTrayQS::AddQSO(CString szName, UINT nID)
{
	CMenu Menu, *pSubMenu;
	if (!Menu.LoadMenu(m_tnd.uID) || !(pSubMenu = Menu.GetSubMenu(0)) )
		return FALSE;

	return pSubMenu->AppendMenu(  MF_STRING, nID, szName);
		
}
