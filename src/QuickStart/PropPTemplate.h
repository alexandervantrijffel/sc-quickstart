#if !defined(AFX_PROPPTEMPLATE_H__940EF667_D3BC_44ED_AD8B_3D172C179435__INCLUDED_)
#define AFX_PROPPTEMPLATE_H__940EF667_D3BC_44ED_AD8B_3D172C179435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPTemplate.h : header file
//

#include "qsoinfo.h"
#include "tasks.h"
/////////////////////////////////////////////////////////////////////////////
// CPropPTemplate dialog

class CPropPTemplate : public CPropertyPageEx
{
	DECLARE_DYNAMIC(CPropPTemplate)

	friend class CAddQSO;
public:
	CPropPTemplate( UINT nIDTemplate, UINT nIDCaption = 0, UINT nIDHeaderTitle = 0, UINT nIDHeaderSubTitle = 0 );
	virtual ~CPropPTemplate();

	const PADDQSO_INFO GetInfo();
	
protected:
	virtual BOOL	OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	
// Implementation
protected:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void CleanUpGDI();	
	void	SetTheIcon(HICON hIcon);
	void	SetBrowseBitmap();
	LRESULT SetCheck(UINT wID);
	LRESULT GetCheck(UINT wID);

	static	ADDQSO_INFO m_Info;
	
	static	HBITMAP m_hBrowse;
	static	HICON m_hIcon;
	static	UINT m_nType;
	static	CTasks m_Tasks;
	static	m_bModify;

	UINT	m_nID;
	BOOL	m_bFirstT;
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PROPPTEMPLATE_H__940EF667_D3BC_44ED_AD8B_3D172C179435__INCLUDED_)
