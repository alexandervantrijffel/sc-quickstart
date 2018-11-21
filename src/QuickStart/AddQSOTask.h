#if !defined(AFX_ADDQSOTASK_H__A2AF311D_6D06_45CF_B0ED_5627952B992B__INCLUDED_)
#define AFX_ADDQSOTASK_H__A2AF311D_6D06_45CF_B0ED_5627952B992B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSOTask.h : header file
//

#include "PropPTemplate.h"\
/////////////////////////////////////////////////////////////////////////////
// CAddQSOTask dialog

class CAddQSOTask : public CPropPTemplate
{
	DECLARE_DYNCREATE(CAddQSOTask)

// Construction
public:
	CAddQSOTask();
	~CAddQSOTask();

// Dialog Data
	//{{AFX_DATA(CAddQSOTask)
	enum { IDD = IDD_ADDQSO_TASK };
	CComboBox	m_ComboDrives;
	CComboBox	m_Combo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAddQSOTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	void Show(UINT ID, BOOL bShow);
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	BOOL m_bDisplayResolutionTipShowed;
	int iPrevSel;
	// Generated message map functions
	//{{AFX_MSG(CAddQSOTask)
	afx_msg void OnSelchange();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL ProcessInput();
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSOTASK_H__A2AF311D_6D06_45CF_B0ED_5627952B992B__INCLUDED_)
