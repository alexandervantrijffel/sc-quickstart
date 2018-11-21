// QSObjects.h: interface for the CQSObjects class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSOBJECTS_H__2E935931_3EAE_4F9F_B00A_98EB40CBCBC3__INCLUDED_)
#define AFX_QSOBJECTS_H__2E935931_3EAE_4F9F_B00A_98EB40CBCBC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "qso.h"
#include "qsoinfo.h"

enum FLIP
{
		FLIP_WITH_BEGIN = 5005
	,	FLIP_WITH_END = 5006
};

class CQSArr
{
public:
	CQSArr();
	virtual ~CQSArr();

	void RemoveAll();
	int Add(PADDQSO_INFOC pInfo);
	BOOL FlipQSO(UINT nIDFirstQS, int iDiffPos);
	UINT GetType(UINT nID);
	void GetInfo(UINT nID, PADDQSO_INFO pInfo);
	int GetObjectPos(UINT nID);
	int Update(UINT nID, PADDQSO_INFO pInfo);
	BOOL Enable(UINT nID, BOOL bEnable);
	void RemoveObject(UINT nID);
	int LoadObjects();
	int Add(PADDQSO_INFO pInfo);
	void ExecuteFromID(UINT nID);
	void ExecuteFromPos(int iPos);
	CString GetHotKey(int iPos);
	CString GetDisplayName(int iPos);
	BOOL	IsEnabled(int iPos);
	HICON	GetIcon(int iPos)	{	return m_ArrQSO[iPos].GetIcon(); }
	int		GetCount()			{	return m_ArrQSO.GetSize();	}
	CString GetPath(int iPos)	{	return m_ArrQSO[iPos].m_szPath;	}
	UINT	GetID(int iPos)		{	return m_ArrQSO[iPos].m_nID;	}

private:
	BOOL SaveObjects();
	void Cleanup();

	static CArray<CQSo,CQSo&> m_ArrQSO;
};

#endif // !defined(AFX_QSOBJECTS_H__2E935931_3EAE_4F9F_B00A_98EB40CBCBC3__INCLUDED_)
