#if !defined(AFX_SELECTPROGRAMDLG_H__E4B85090_1613_497F_AA95_B904E111169E__INCLUDED_)
#define AFX_SELECTPROGRAMDLG_H__E4B85090_1613_497F_AA95_B904E111169E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectProgramDlg.h : header file
//

#include "iconlistbox.h"
/////////////////////////////////////////////////////////////////////////////
// CSelectProgramDlg dialog

class CSelectProgramDlg : public CDialog
{
// Construction
public:
	CSelectProgramDlg(CWnd* pParent = NULL);   // standard constructor
	CString GetPathName();
	~CSelectProgramDlg();

// Dialog Data
	//{{AFX_DATA(CSelectProgramDlg)
	enum { IDD = IDD_SELECT_PROGRAM };
	CIconListBox 	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectProgramDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_szPath;
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CSelectProgramDlg)
	virtual void OnOK();
	afx_msg void OnOther();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchange();
	afx_msg void OnDblclk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTPROGRAMDLG_H__E4B85090_1613_497F_AA95_B904E111169E__INCLUDED_)
