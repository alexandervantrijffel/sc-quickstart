// Crc.h: interface for the CCrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRC_H__5098191A_D91B_45A3_BEB6_02A0D95E1DBC__INCLUDED_)
#define AFX_CRC_H__5098191A_D91B_45A3_BEB6_02A0D95E1DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCrc  
{
public:
	DWORD StringCrc(LPCTSTR szString, DWORD &dwCrc) const;
	DWORD FileCrcAsm(LPCTSTR szFileName, DWORD& dwCrc32) const;
	void Free();
	void Init();
	CCrc();
	virtual ~CCrc();

protected:
	inline void CalcCrc(const BYTE byte, DWORD &dwCrc32) const;

private:
	DWORD *m_pdwCrcTable;

};

#endif // !defined(AFX_CRC_H__5098191A_D91B_45A3_BEB6_02A0D95E1DBC__INCLUDED_)
