// TipsMgr.cpp: implementation of the CTipsMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "TipsMgr.h"

#include "tips.h"
#include "settings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTipsMgr::CTipsMgr()
{

}

CTipsMgr::~CTipsMgr()
{

}

BOOL CTipsMgr::ShowTip(int nTip, BOOL bAlways)
{
	CSettings set;
	BOOL bRet=FALSE;
	DWORD dwTips = set.GetDW(IDS_SETTINGS_NOTIPS);

	if (dwTips == -1 || !(ID_TIP_MODIFYQSO & dwTips))
	{
		CTips Tip(nTip);
		if (Tip.DoModal() == IDCANCEL)
		{
			if (dwTips==-1)
				dwTips=ID_TIP_MODIFYQSO;
			else
				dwTips ^= ID_TIP_MODIFYQSO;
				set.Set(IDS_SETTINGS_NOTIPS, dwTips);
		}
		bRet=TRUE;
	}
	return bRet;
}
