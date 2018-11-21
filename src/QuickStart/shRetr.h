// SHRetr.h: interface for the CIconRetr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICONRETR_H__039EBF0A_0D2C_4BBE_8C4C_1B79C568188E__INCLUDED_)
#define AFX_ICONRETR_H__039EBF0A_0D2C_4BBE_8C4C_1B79C568188E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSHRetr  
{
public:
	static HCURSOR	GetHandCursor();
	static BOOL		InvokeCmd(int nFolder, LPCTSTR szVerb);
	static HICON	GetSpecialFolderIcon(int nFolder);
	static HICON	GetIcon( LPITEMIDLIST lpi, BOOL bSmallIcon );
	
	static HICON	GetIcon(LPCTSTR szFile, UINT nIndex);
	static HICON	GetIcon(LPCTSTR szPath);
	static HICON	GetFolderIcon();
	static HICON	GetURLIcon();
	static HICON	GetCDIcon();
	
	static CString	GetAppPath(LPCTSTR szFileName);
	static CString	GetAllCDDrives();

	CSHRetr();
	virtual ~CSHRetr();

private:
	static HICON GetIconFromRegString(LPTSTR szFormattedString);
};

#endif // !defined(AFX_ICONRETR_H__039EBF0A_0D2C_4BBE_8C4C_1B79C568188E__INCLUDED_)
