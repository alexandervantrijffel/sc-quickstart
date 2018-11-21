// QuickStartDlg.h : header file
//

#if !defined(AFX_QUICKSTARTDLG_H__7AF916F5_EEB1_4F09_B714_BFB47A4ACB8B__INCLUDED_)
#define AFX_QUICKSTARTDLG_H__7AF916F5_EEB1_4F09_B714_BFB47A4ACB8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "qsobjects.h"

#include "qsbtn.h"
#include "systemtray.h"

/////////////////////////////////////////////////////////////////////////////
// CQuickStartDlg dialog

class CQuickStartDlg : public CDialog
{
// Construction
public:
	CQuickStartDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQuickStartDlg)
	enum { IDD = IDD_QUICKSTART_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickStartDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
		
// Implementation
protected:
	void EnableQSBtn(int iPos, BOOL bEnable);
	void OnRemoveAll(WPARAM wParam, LPARAM lParam);
	void OnLoadDefConfig(WPARAM wReplace, LPARAM lParam);
	void OnQSSysMenu(UINT nID);
	void OnCmdSysTray(UINT nID);
	void UpdateAllQSBtn();
	BOOL OnCTCmd(UINT nCmdID, long lQSID);
	void InitializeBtn(CButtonST& btn);

	HICON		m_hIcon;
	UINT		m_nFirstDisplayedQS;
	CQSArr		m_QSOArr;
	CQSBtn		m_QSBtn[8];
	CButtonST	m_BtnUp;
	CButtonST	m_BtnDown;
	CButtonST	m_StBtn[4];
	CSystemTray	m_SysTray;
	HACCEL		m_hAccel;
	BOOL		m_bShowStart;

	// Generated message map functions
	//{{AFX_MSG(CQuickStartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnAddQSO();
	afx_msg void OnDown();
	afx_msg void OnUp();
	afx_msg void OnHide();
	afx_msg void OnClose();
	afx_msg void OnConfig();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnAbout();
	//}}AFX_MSG
	void OnQSBtn(UINT ID);
	afx_msg void OnHotKey(WPARAM idHotKey, LPARAM KeyData);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	void OnFillSysTrayMenu(WPARAM w, LPARAM hMenu);
 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICKSTARTDLG_H__7AF916F5_EEB1_4F09_B714_BFB47A4ACB8B__INCLUDED_)
