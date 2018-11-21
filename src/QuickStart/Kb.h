// Kb.h: interface for the CKb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KB_H__D9D16F93_2F76_4339_A1FA_BBD97463F488__INCLUDED_)
#define AFX_KB_H__D9D16F93_2F76_4339_A1FA_BBD97463F488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKb  
{
public:
	CString GetText(DWORD dwHotKey);
	BOOL IsControl(UINT nVirtKey);
	void Init();
	WORD GetKey(CString szText);
	CString GetText(UINT nVirtKey);
	CKb();
	virtual ~CKb();

private:
	Add(CString& szResult, UINT nVirtKey);
	CStringArray m_Keys;
	CUIntArray m_VirtKeys;

};

#endif // !defined(AFX_KB_H__D9D16F93_2F76_4339_A1FA_BBD97463F488__INCLUDED_)
