// QSObjects.cpp: implementation of the CQSArr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "QSObjects.h"

#include "kb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CArray<CQSo,CQSo&> CQSArr::m_ArrQSO;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSArr::CQSArr()
{
}

CQSArr::~CQSArr()
{
	Cleanup();
}

int CQSArr::Add(PADDQSO_INFO pInfo)
{
	CQSo qso;
	if (qso.Create(pInfo))
	{
		int iPos = m_ArrQSO.Add(qso);
		if ( iPos!=-1 && (!pInfo->dwHotKey || m_ArrQSO[iPos].Enable(TRUE)) && SaveObjects())
			return iPos;
	}

	return -1;
}

int CQSArr::Update(UINT nID, PADDQSO_INFO pInfo)
{
	int iPos = GetObjectPos(nID);
	
	m_ArrQSO[iPos].Enable(FALSE);

	m_ArrQSO[iPos].m_dwHotKey = pInfo->dwHotKey;
	m_ArrQSO[iPos].m_szName = pInfo->szName;
	m_ArrQSO[iPos].m_szOpt = pInfo->szOpt;
	m_ArrQSO[iPos].m_szPath = pInfo->szPath;
	
	if ( (!pInfo->dwHotKey || m_ArrQSO[iPos].Enable(TRUE)) && SaveObjects())
		return iPos;
	
	return -1;
}


void CQSArr::ExecuteFromID(UINT nID)
{
	int iPos = GetObjectPos(nID);

	if (!m_ArrQSO[iPos].Execute())
		AfxMessageBox(IDS_PATHNOTFOUND, MB_ICONSTOP | MB_SETFOREGROUND);
}
void CQSArr::ExecuteFromPos(int iPos)
{
	ASSERT(iPos < m_ArrQSO.GetSize());
	
	if (!m_ArrQSO[iPos].Execute())
		AfxMessageBox(IDS_PATHNOTFOUND, MB_ICONSTOP | MB_SETFOREGROUND);
}
void CQSArr::Cleanup()
{
	for (int i=0;i<=m_ArrQSO.GetUpperBound();i++)
	{
		m_ArrQSO[i].Enable(FALSE);
		
		if (m_ArrQSO[i].m_hIcon)
			DeleteObject(m_ArrQSO[i].m_hIcon);
	}
	
	m_ArrQSO.RemoveAll();
}

int CQSArr::GetObjectPos(UINT nID)
{
	for (int i=0;i<m_ArrQSO.GetSize();i++)
	{
		if (m_ArrQSO[i].m_nID == nID)
			return i;
	}

	ASSERT(0);
	return -1;
}

// load all qsobjects from data file
// function returns itemcount
int CQSArr::LoadObjects()
{
	CFile File;
	int icLoaded=0;
	
	char szPath[MAX_PATH];
	GetSystemDirectory(szPath, MAX_PATH);
	strcat(szPath, "\\qs.dat");
	
	if (File.Open(szPath, CFile::modeRead))
	{
		CArchive ar(&File, CArchive::load);

		// get itemcount
		int icItems=0;
		File.Read(&icItems, sizeof(icItems));
		
		for ( ; icLoaded<icItems ; icLoaded++)
		{
			CQSo qso;
			qso.Serialize(ar);
			qso.GetType();

			if (qso.m_bActive)
			{
				qso.m_bActive = FALSE;
				qso.Enable(TRUE);
			}

			m_ArrQSO.Add(qso);
		}	
	}
	return icLoaded;
}

BOOL CQSArr::SaveObjects()
{
	CFile File;
	BOOL bRet=FALSE;
	
	char szPath[MAX_PATH];
	GetSystemDirectory(szPath, MAX_PATH);
	strcat(szPath, "\\qs.dat");
	
	if (File.Open(szPath, CFile::modeWrite|CFile::modeCreate))
	{
		CArchive ar(&File, CArchive::store);

		// write itemcount
		int icItems = m_ArrQSO.GetSize();
		File.Write(&icItems, sizeof(icItems));
		
		int iCur=-1;

		while (++iCur<icItems)
			m_ArrQSO[iCur].Serialize(ar);
		return TRUE;
	}
	return FALSE;
}

void CQSArr::RemoveObject(UINT nID)
{
	int iPos = GetObjectPos(nID);
	
	m_ArrQSO[iPos].Enable(FALSE);
	m_ArrQSO.RemoveAt(iPos);

	SaveObjects();

	// schuif alle elementen vanaf 1 positie na het te verwijderen object
	// 1 plaats terug
	// int iLast = m_ArrQSO.GetUpperBound();
	//for ( Pos+=1 ; i<=iLast ; i++)
	//	m_ArrQSO.SetAt( iPos-1, m_ArrQSO[iPos );

}

void CQSArr::RemoveAll()
{
	for (int i=0 ; i<m_ArrQSO.GetSize() ; i++)
		m_ArrQSO[i].Enable(FALSE);

	m_ArrQSO.RemoveAll();

	SaveObjects();

}



BOOL CQSArr::Enable(UINT nID, BOOL bEnable)
{
	BOOL bRet = m_ArrQSO[GetObjectPos(nID)].Enable(bEnable);
	SaveObjects();
	
	return bRet;
}

CString CQSArr::GetHotKey(int iPos)
{
	if (m_ArrQSO[iPos].m_dwHotKey)
	{
		CKb kb;
		return kb.GetText(m_ArrQSO[iPos].m_dwHotKey);
	}
	else
		return IDS_NOHOTKEY;
}

CString CQSArr::GetDisplayName(int iPos)
{
	if (m_ArrQSO[iPos].m_szName.GetLength() <= SCQ_MAXDISPLAYCHARS)
		return m_ArrQSO[iPos].m_szName;
	
	CString szName = m_ArrQSO[iPos].m_szName.Left(SCQ_MAXDISPLAYCHARS-4);
	szName += "[..]";
	return szName;
}
 
BOOL CQSArr::IsEnabled(int iPos)
{
	return (m_ArrQSO[iPos].m_bActive || m_ArrQSO[iPos].m_dwHotKey == 0);
}

void CQSArr::GetInfo(UINT nID, PADDQSO_INFO pInfo)
{
	int iPos = GetObjectPos(nID);
	pInfo->dwHotKey = m_ArrQSO[iPos].m_dwHotKey;
	pInfo->szName	= m_ArrQSO[iPos].m_szName;
	pInfo->szOpt	= m_ArrQSO[iPos].m_szOpt;
	pInfo->szPath	= m_ArrQSO[iPos].m_szPath;
}

UINT CQSArr::GetType(UINT nID)
{
	return m_ArrQSO[GetObjectPos(nID)].GetType();
}

BOOL CQSArr::FlipQSO(UINT nID, int iDiffPos)
{
	int iPosFirst = GetObjectPos(nID);

	int iTargetPos=-1;

	if (iDiffPos == FLIP_WITH_BEGIN)
		iTargetPos=0;
	else if (iDiffPos == FLIP_WITH_END)
		iTargetPos = GetCount()-1;
	else
		iTargetPos = iPosFirst + iDiffPos;
		
	if (iPosFirst == -1 || iTargetPos < 0 || iTargetPos > m_ArrQSO.GetUpperBound() || iTargetPos == iPosFirst)
		return FALSE;

	int iDiff = (iTargetPos<iPosFirst) ? -1 : 1;
	
	while ( iPosFirst != iTargetPos)
	{
		CQSo qsobak(m_ArrQSO[iPosFirst+iDiff]);
	
		m_ArrQSO.SetAt(iPosFirst+iDiff, m_ArrQSO.GetAt(iPosFirst));
		m_ArrQSO.SetAt(iPosFirst, qsobak);

		iPosFirst += iDiff;
	}
	
	return SaveObjects();
}
