// QSBtn.h: interface for the CQSBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSBTN_H__A1DEAC9F_C5E6_401A_99B8_93DED3857205__INCLUDED_)
#define AFX_QSBTN_H__A1DEAC9F_C5E6_401A_99B8_93DED3857205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "btnst.h"

class CQSBtn : public CButtonST
{
public:
	void EnableIT(BOOL bEnable);
	void Init();
	UINT GetID();
	void Update(CString szName, CString szHotKey, HICON hIcon, UINT nID);
	CQSBtn();
	virtual ~CQSBtn();

protected:
	void OnCTCmd(UINT nID);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:	
	static CFont m_TitleFont;
	static CFont m_ShortFont;

	CString m_szShortKey;
	UINT	m_nID;
	BOOL	m_bEnabled;

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	DECLARE_MESSAGE_MAP();
};

#endif // !defined(AFX_QSBTN_H__A1DEAC9F_C5E6_401A_99B8_93DED3857205__INCLUDED_)
