// RegDlg.h : header file
//

#if !defined(AFX_REGDLG_H__1F896C6B_511B_4281_A71D_F1C6FFE8317E__INCLUDED_)
#define AFX_REGDLG_H__1F896C6B_511B_4281_A71D_F1C6FFE8317E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

class CRegDlg : public CDialog
{
// Construction
public:
	CString GetRegistrationNumber(CString szName);
	CRegDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__1F896C6B_511B_4281_A71D_F1C6FFE8317E__INCLUDED_)
