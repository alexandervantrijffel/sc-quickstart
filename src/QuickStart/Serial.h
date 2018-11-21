// Serial.h: interface for the CSerial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIAL_H__9DEE7038_91BD_4A22_9F84_70B3FF1252C8__INCLUDED_)
#define AFX_SERIAL_H__9DEE7038_91BD_4A22_9F84_70B3FF1252C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSerial  
{
	enum 
	{
			SERIAL_FILE=0
		,	SERIAL_REG1
		,	SERIAL_REG2
	};
public:
	BOOL Register(CString szName, CString szSerial);
	CSerial();
	virtual ~CSerial();
	int GetTrialDaysLeft();

private:
	DWORD m_dwExeDataPos;
	CString m_szFilePath, m_szRegPath1, m_szRegPath2,m_szRegVal1,m_szRegVal2;
	int m_nMaxTrialDays;
protected:
	BOOL IsValid(LPSYSTEMTIME lpST);
	void SetData(LPSYSTEMTIME lpST, int iIndex);
};

#endif // !defined(AFX_SERIAL_H__9DEE7038_91BD_4A22_9F84_70B3FF1252C8__INCLUDED_)
