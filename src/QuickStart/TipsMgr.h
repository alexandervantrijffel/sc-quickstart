// TipsMgr.h: interface for the CTipsMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIPSMGR_H__4BE780A8_E32F_4D94_91FD_76979445D0E6__INCLUDED_)
#define AFX_TIPSMGR_H__4BE780A8_E32F_4D94_91FD_76979445D0E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ID_TIP_MODIFYQSO				IDD_TIP_MODIFYQSO
#define ID_TIP_DISPLAYRESOLUTION		IDD_TIP_DISPLAYRESOLUTION
#define ID_TIP_DISPLAYRESOLUTION_TEST	IDD_TIP_DISPLAYRESOLUTION_TEST

class CTipsMgr  
{
public:
	BOOL ShowTip(int nTip, BOOL bAlways=FALSE);
	CTipsMgr();
	virtual ~CTipsMgr();

};

#endif // !defined(AFX_TIPSMGR_H__4BE780A8_E32F_4D94_91FD_76979445D0E6__INCLUDED_)
