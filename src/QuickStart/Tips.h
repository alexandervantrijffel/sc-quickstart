#if !defined(AFX_TIPS_H__D9AED3F0_2754_475F_8E1D_30B645002C28__INCLUDED_)
#define AFX_TIPS_H__D9AED3F0_2754_475F_8E1D_30B645002C28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tips.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTips dialog

class CTips : public CDialog
{
// Construction
public:
	CTips(UINT IDD, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTips)
//	enum { IDD = IDD_TIP_MODIFYQSO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTips)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EndDlg();
	void OnCancel();

	// Generated message map functions
	//{{AFX_MSG(CTips)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPS_H__D9AED3F0_2754_475F_8E1D_30B645002C28__INCLUDED_)
