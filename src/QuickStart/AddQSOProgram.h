#if !defined(AFX_ADDQSOPROGRAM_H__831173DD_F219_46F5_8253_DB087EAA74A8__INCLUDED_)
#define AFX_ADDQSOPROGRAM_H__831173DD_F219_46F5_8253_DB087EAA74A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSOProgram.h : header file
//

#include "PropPTemplate.h"
/////////////////////////////////////////////////////////////////////////////
// CAddQSOProgram dialog

class CAddQSOProgram : public CPropPTemplate
{
	DECLARE_DYNCREATE(CAddQSOProgram)

// Construction
public:
	CAddQSOProgram();
	~CAddQSOProgram();
	
// Dialog Data
	//{{AFX_DATA(CAddQSOProgram)
	enum { IDD = IDD_ADDQSO_PROGRAM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAddQSOProgram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddQSOProgram)
	afx_msg void OnBrowse();
	afx_msg void OnUpdatePath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSOPROGRAM_H__831173DD_F219_46F5_8253_DB087EAA74A8__INCLUDED_)
