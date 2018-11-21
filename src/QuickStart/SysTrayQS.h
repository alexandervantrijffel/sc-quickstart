// SysTrayQS.h: interface for the CSysTrayQS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTRAYQS_H__DAC2C42B_5E24_4034_918A_B26FEC788CAE__INCLUDED_)
#define AFX_SYSTRAYQS_H__DAC2C42B_5E24_4034_918A_B26FEC788CAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "systemtray.h"

class CSysTrayQS  :	public CSystemTray
{
	DECLARE_DYNAMIC(CSysTrayQS);

public:
	BOOL AddQSO(CString szName, UINT nID);
	CSysTrayQS();
	virtual ~CSysTrayQS();

};

#endif // !defined(AFX_SYSTRAYQS_H__DAC2C42B_5E24_4034_918A_B26FEC788CAE__INCLUDED_)
