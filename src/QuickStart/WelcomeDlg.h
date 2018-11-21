#if !defined(AFX_WELCOMEDLG_H__EC4FBE53_A0C4_46CF_8ED7_3417E7DD5987__INCLUDED_)
#define AFX_WELCOMEDLG_H__EC4FBE53_A0C4_46CF_8ED7_3417E7DD5987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomeDlg.h : header file
//
#include "hyperlink.h"
/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg dialog

class CWelcomeDlg : public CDialog
{
// Construction
public:
	CWelcomeDlg(int iDaysLeft,CWnd* pParent = NULL);   // standard constructor
	CFont m_CounterFont;
// Dialog Data
	//{{AFX_DATA(CWelcomeDlg)
	enum { IDD = IDD_WELCOME };
	CHyperLink	m_WebSupport;
	CHyperLink	m_WebHome;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	short m_nSecs;
	int m_nTrialDaysLeft;
	HCURSOR m_hBtnCursor;

	// Generated message map functions
	//{{AFX_MSG(CWelcomeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRegister();
	afx_msg void OnBuy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEDLG_H__EC4FBE53_A0C4_46CF_8ED7_3417E7DD5987__INCLUDED_)
