// qsoinfo.h: interface for the qsoinfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSOINFO_H__B459A6B8_1D3A_4632_8BBD_CD8A32A12F5A__INCLUDED_)
#define AFX_QSOINFO_H__B459A6B8_1D3A_4632_8BBD_CD8A32A12F5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __AFX_H__
typedef struct ADDQSO_INF
{
	CString szName;
	CString szPath;
	CString szOpt;
	DWORD	dwHotKey;
}ADDQSO_INFO, *PADDQSO_INFO;

typedef struct QSO_INF
{
 	CString szName;
	CString szHotKey;
	UINT nID;
	HICON hIcon;
}QSO_INFO, *PQSO_INFO;

#endif

typedef struct ADDQSO_INFC
{
	LPTSTR szName;
	LPTSTR szPath;
	LPTSTR szOpt;
	DWORD  dwHotKey;
}ADDQSO_INFOC, *PADDQSO_INFOC;



#endif // !defined(AFX_QSOINFO_H__B459A6B8_1D3A_4632_8BBD_CD8A32A12F5A__INCLUDED_)
