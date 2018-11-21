#if !defined(AFX_ADDQSODOC_H__4641709B_39B9_446A_B808_06DB43E7D3C3__INCLUDED_)
#define AFX_ADDQSODOC_H__4641709B_39B9_446A_B808_06DB43E7D3C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSODoc.h : header file
//

#include "PropPTemplate.h"
/////////////////////////////////////////////////////////////////////////////
// CAddQSODoc dialog

class CAddQSODoc : public CPropPTemplate
{
	DECLARE_DYNCREATE(CAddQSODoc)

// Construction
public:
	CAddQSODoc();
	~CAddQSODoc();

// Dialog Data
	//{{AFX_DATA(CAddQSODoc)
	enum { IDD = IDD_ADDQSO_DOC };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAddQSODoc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	// Generated message map functions
	//{{AFX_MSG(CAddQSODoc)
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSODOC_H__4641709B_39B9_446A_B808_06DB43E7D3C3__INCLUDED_)
