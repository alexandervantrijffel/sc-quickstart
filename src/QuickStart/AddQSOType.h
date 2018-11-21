#if !defined(AFX_ADDQSOTYPE_H__82B3A6EF_0688_4CE6_8DFF_91D3D11AD76D__INCLUDED_)
#define AFX_ADDQSOTYPE_H__82B3A6EF_0688_4CE6_8DFF_91D3D11AD76D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSOType.h : header file
//

#include "PropPTemplate.h"
/////////////////////////////////////////////////////////////////////////////
// CAddQSOType dialog

class CAddQSOType : public CPropPTemplate
{
	DECLARE_DYNCREATE(CAddQSOType)

// Construction
public:
	CAddQSOType();
	~CAddQSOType();

// Dialog Data
	//{{AFX_DATA(CAddQSOType)
	enum { IDD = IDD_ADDQSO_TYPE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAddQSOType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL	OnSetActive();
	virtual LRESULT OnWizardNext();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAddQSOType)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSOTYPE_H__82B3A6EF_0688_4CE6_8DFF_91D3D11AD76D__INCLUDED_)
