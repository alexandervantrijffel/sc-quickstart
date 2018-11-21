#if !defined(AFX_ADDQSOHOTKEY_H__981024A5_089F_438B_AAC7_E18D6396D5BC__INCLUDED_)
#define AFX_ADDQSOHOTKEY_H__981024A5_089F_438B_AAC7_E18D6396D5BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSOHotKey.h : header file
//

#include "PropPTemplate.h"
/////////////////////////////////////////////////////////////////////////////
// CAddQSOHotKey dialog

class CAddQSOHotKey : public CPropPTemplate
{
	DECLARE_DYNCREATE(CAddQSOHotKey)

// Construction
public:
	CAddQSOHotKey();
	~CAddQSOHotKey();

// Dialog Data
	//{{AFX_DATA(CAddQSOHotKey)
	enum { IDD = IDD_ADDQSO_HOTKEY };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAddQSOHotKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnSetActive();
	// Generated message map functions
	//{{AFX_MSG(CAddQSOHotKey)
	afx_msg void OnRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSOHOTKEY_H__981024A5_089F_438B_AAC7_E18D6396D5BC__INCLUDED_)
