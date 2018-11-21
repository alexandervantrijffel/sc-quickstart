#if !defined(AFX_ADDQSOHOTKEYRECORD_H__1859E5D2_0762_4CE7_AB22_556BF5312612__INCLUDED_)
#define AFX_ADDQSOHOTKEYRECORD_H__1859E5D2_0762_4CE7_AB22_556BF5312612__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSOHotKeyRecord.h : header file
//
#include "kb.h"


/////////////////////////////////////////////////////////////////////////////
// CAddQSOHotKeyRecord dialog

class CAddQSOHotKeyRecord : public CDialog
{
// Construction
public:
	CAddQSOHotKeyRecord(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddQSOHotKeyRecord();

protected:
// Dialog Data
	//{{AFX_DATA(CAddQSOHotKeyRecord)
	enum { IDD = IDD_ADDQSO_HOTKEY_RECORD };
	CString	m_szHotKey;
	//}}AFX_DATA

	static LRESULT CALLBACK KeyboardProc( int code, WPARAM wParam,	LPARAM lParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddQSOHotKeyRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	BOOL Test();
	DWORD GetHotKey() { return m_dwHotKey; }
	CString GetHotKeyText() { return m_szHotKey; }
	

// Implementation
protected:
	DWORD m_dwHotKey;
	HHOOK m_hHook;
	CKb m_Kb;

	// Generated message map functions
	//{{AFX_MSG(CAddQSOHotKeyRecord)
	afx_msg void OnReset();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSOHOTKEYRECORD_H__1859E5D2_0762_4CE7_AB22_556BF5312612__INCLUDED_)
