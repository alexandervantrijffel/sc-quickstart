// Reg.h : main header file for the REG application
//

#if !defined(AFX_REG_H__192C2AD9_BE95_44F0_9548_8D31208FA374__INCLUDED_)
#define AFX_REG_H__192C2AD9_BE95_44F0_9548_8D31208FA374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegApp:
// See Reg.cpp for the implementation of this class
//

class CRegApp : public CWinApp
{
public:
	CRegApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REG_H__192C2AD9_BE95_44F0_9548_8D31208FA374__INCLUDED_)
