#if !defined(AFX_ADDQSONAME_H__BB38B72E_ADB7_458D_93C7_BC77BEA481A8__INCLUDED_)
#define AFX_ADDQSONAME_H__BB38B72E_ADB7_458D_93C7_BC77BEA481A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSOName.h : header file
//

#include "PropPTemplate.h"
/////////////////////////////////////////////////////////////////////////////
// CAddQSOName dialog

class CAddQSOName : public CPropPTemplate
{
	DECLARE_DYNCREATE(CAddQSOName)

// Construction
public:
	CAddQSOName();
	~CAddQSOName();

// Dialog Data
	//{{AFX_DATA(CAddQSOName)
	enum { IDD = IDD_ADDQSO_NAME };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAddQSOName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	// Generated message map functions
	//{{AFX_MSG(CAddQSOName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSONAME_H__BB38B72E_ADB7_458D_93C7_BC77BEA481A8__INCLUDED_)
