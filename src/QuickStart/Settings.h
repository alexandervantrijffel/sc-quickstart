// Settings.h: interface for the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGS_H__36949CB0_4783_45E6_BE1C_A9273CDED155__INCLUDED_)
#define AFX_SETTINGS_H__36949CB0_4783_45E6_BE1C_A9273CDED155__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettings  
{
public:
	int GetB(LPCTSTR szValueName, LPBYTE pData, DWORD* pdwcb);
	void EnableAutoStart(BOOL bEnable);
	DWORD GetDW(LPCTSTR szValueName, DWORD dwDefaultSetting=-1);
	CString GetS(LPCTSTR szValueName);
	void Set(LPCTSTR szValueName, DWORD dwValue);
	void Set(LPCTSTR szValueName, LPCTSTR szValue);
	void Set(LPCTSTR szValueName, BYTE* pData, DWORD dwcbData);
	CSettings();
	virtual ~CSettings();

protected:
	HKEY GetRootKey(REGSAM Sam);
};

#endif // !defined(AFX_SETTINGS_H__36949CB0_4783_45E6_BE1C_A9273CDED155__INCLUDED_)
