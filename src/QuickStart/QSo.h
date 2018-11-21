// QSo.h: interface for the CQSo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSO_H__AC104B86_7118_4E3E_A5E2_7CFA3588BCFA__INCLUDED_)
#define AFX_QSO_H__AC104B86_7118_4E3E_A5E2_7CFA3588BCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "qsoinfo.h"

	enum type {
		  QSO_TYPE_NONE=0
		, QSO_TYPE_PROGRAM=IDD_ADDQSO_PROGRAM
		, QSO_TYPE_TASK=IDD_ADDQSO_TASK
		, QSO_TYPE_FOLDER=IDD_ADDQSO_FOLDER
		, QSO_TYPE_DOC=IDD_ADDQSO_DOC
	};


class CQSo  : public CObject
{
	enum status {
		QSO_HOTKEY_NOTUSED=-1
	};

	friend class CQSArr;
public:
	BOOL	Create(PADDQSO_INFO pINFO);
	BOOL	Enable(BOOL bEnable);
	BOOL	Execute();
	HICON	GetIcon();
	UINT	GetType();
	
	CQSo();
	CQSo(CQSo&);
	virtual ~CQSo();
	CQSo& operator=(CQSo&);
	
private:
	BOOL	CreateProc(LPCTSTR szApp, LPCTSTR szCmdLine);

	CString m_szName;
	CString m_szPath;
	CString m_szOpt;
	HICON	m_hIcon;	
	BOOL	m_bActive;
	DWORD	m_dwHotKey;
	UINT	m_nType;
	UINT	m_nID;
	
	static UINT m_nNextHotID;

	virtual void Serialize(CArchive& ar);
	DECLARE_DYNAMIC(CQSo);
};

#endif // !defined(AFX_QSO_H__AC104B86_7118_4E3E_A5E2_7CFA3588BCFA__INCLUDED_)
