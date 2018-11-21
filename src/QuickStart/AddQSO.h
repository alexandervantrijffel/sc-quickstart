#if !defined(AFX_ADDQSO_H__A3CB54D9_C2D3_4835_BF19_88420F55B3A2__INCLUDED_)
#define AFX_ADDQSO_H__A3CB54D9_C2D3_4835_BF19_88420F55B3A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddQSO.h : header file
//


#include "AddQSOType.h"
#include "AddQSOProgram.h"
#include "AddQSOTask.h"
#include "AddQSOFolder.h"
#include "AddQSODoc.h"
#include "AddQSOHotKey.h"
#include "AddQSOName.h"
#include "AddQSOSum.h"

#include "qsoinfo.h"
/////////////////////////////////////////////////////////////////////////////
// CAddQSO

class CAddQSO : public CPropertySheetEx
{
	DECLARE_DYNAMIC(CAddQSO)
	
// Construction
public:
	// adding:
	CAddQSO(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, HBITMAP hbmWatermark = NULL, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
	// modifying:
	CAddQSO::CAddQSO(UINT nIDCaption, PADDQSO_INFO pInfo, UINT nType, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, HBITMAP hbmWatermark = NULL, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
	
// Attributes
public:
	CAddQSOType		m_Type;
	CAddQSOProgram	m_Program;
	CAddQSOTask		m_Task;
	CAddQSODoc		m_Doc;
	CAddQSOFolder	m_Folder;
	CAddQSOHotKey	m_HotKey;
	CAddQSOName		m_Name;
	CAddQSOSum		m_Sum;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddQSO)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	const PADDQSO_INFO GetInfo();
	virtual ~CAddQSO();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAddQSO)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDQSO_H__A3CB54D9_C2D3_4835_BF19_88420F55B3A2__INCLUDED_)
