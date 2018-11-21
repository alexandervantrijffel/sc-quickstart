// Kb.cpp: implementation of the CKb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "Kb.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKb::CKb()
{
	Init();
}

CKb::~CKb()
{
	m_Keys.RemoveAll();
	m_VirtKeys.RemoveAll();
}

CKb::Add(CString &szResult, UINT nVirtKey)
{
	if (szResult.GetLength())
		szResult += " + ";
	szResult += GetText(nVirtKey);
}

CString CKb::GetText(DWORD dwHotKey)
{
	CString szResult;
	if (dwHotKey & SCQ_MOD_CTRL)
		Add(szResult, 17);
	if (dwHotKey & SCQ_MOD_SHIFT)
		Add(szResult, 16);
	if (dwHotKey & SCQ_MOD_ALT)
		Add(szResult, 18);
	if (dwHotKey & SCQ_MOD_WIN)
		Add(szResult, 91);

	Add(szResult, dwHotKey & 0xFF);
	szResult.TrimRight(" +");
	return szResult;
}


CString CKb::GetText(UINT nVirtKey)
{
	
	if (nVirtKey>47&&nVirtKey<59||nVirtKey>64&&nVirtKey<91)	// check for normal ASCII character
	{
		return nVirtKey;
	}
	else
	{
		for (int i=0; i<m_VirtKeys.GetSize(); i++)
		{
			if (nVirtKey == m_VirtKeys[i])
				return m_Keys[i];
		}
	}

	return "";
}

WORD CKb::GetKey(CString szText)
{
	for (int i=0; i<m_Keys.GetSize(); i++)
	{
		if (szText == m_Keys[i])
			return m_VirtKeys[i];
	}
	return 0;
}


BOOL CKb::IsControl(UINT nVirtKey)
{
	return ( 
			nVirtKey==m_VirtKeys[4]
		||	nVirtKey==m_VirtKeys[5]
		||	nVirtKey==m_VirtKeys[6]
		||	nVirtKey==m_VirtKeys[22]);
}

void CKb::Init()
{
	m_Keys.SetSize(48);
	m_VirtKeys.SetSize(48);
	m_VirtKeys[0]	= 0;	m_Keys[0]	= "";
	
	m_VirtKeys[1]	= 8;	m_Keys[1]	= "BACKSPACE";
	m_VirtKeys[2]	= 9;	m_Keys[2]	= "TAB";
	m_VirtKeys[3]	= 13;	m_Keys[3]	= "RETURN";
	m_VirtKeys[4]	= 16;	m_Keys[4]	= "SHIFT";
	m_VirtKeys[5]	= 17;	m_Keys[5]	= "CTRL"; 
	m_VirtKeys[6]	= 18;	m_Keys[6]	= "ALT";
	m_VirtKeys[7]	= 19;	m_Keys[7]	= "BREAK";
	m_VirtKeys[8]	= 20;	m_Keys[8]	= "CAPSLOCK";
	m_VirtKeys[9]	= 27;	m_Keys[9]	= "ESC";
	m_VirtKeys[10]	= 32;	m_Keys[10]	= "SPACE";
	m_VirtKeys[11]	= 33;	m_Keys[11]	= "PAGEUP";
	m_VirtKeys[12]	= 34;	m_Keys[12]	= "PAGEDN";
	m_VirtKeys[13]	= 35;	m_Keys[13]	= "END";
	m_VirtKeys[14]	= 36;	m_Keys[14]	= "HOME";
	m_VirtKeys[15]	= 37;	m_Keys[15]	= "LEFT";
	m_VirtKeys[16]	= 38;	m_Keys[16]	= "UP";
	m_VirtKeys[17]	= 39;	m_Keys[17]	= "RIGHT";
	m_VirtKeys[18]	= 40;	m_Keys[18]	= "DOWN";
	m_VirtKeys[19]	= 44;	m_Keys[19]	= "PRINTSCREEN";
	m_VirtKeys[20]	= 45;	m_Keys[20]	= "INS";
	m_VirtKeys[21]	= 46;	m_Keys[21]	= "DEL";
	m_VirtKeys[22]	= 91;	m_Keys[22]	= "WIN-START";
	m_VirtKeys[23]	= 93;	m_Keys[23]	= "WIN-CONTEXT";
	m_VirtKeys[24]	= 112;	m_Keys[24]	= "F1";
	m_VirtKeys[25]	= 113;	m_Keys[25]	= "F2";
	m_VirtKeys[26]	= 114;	m_Keys[26]	= "F3";
	m_VirtKeys[27]	= 115;	m_Keys[27]	= "F4";
	m_VirtKeys[28]	= 116;	m_Keys[28]	= "F5";
	m_VirtKeys[29]	= 117;	m_Keys[29]	= "F6";
	m_VirtKeys[30]	= 118;	m_Keys[30]	= "F7";
	m_VirtKeys[31]	= 119;	m_Keys[31]	= "F8";
	m_VirtKeys[32]	= 120;	m_Keys[32]	= "F9";
	m_VirtKeys[33]	= 121;	m_Keys[33]	= "F10";
	m_VirtKeys[34]	= 122;	m_Keys[34]	= "F11";
	m_VirtKeys[35]	= 123;	m_Keys[35]	= "F12";
	m_VirtKeys[36]	= 186;	m_Keys[36]	= ";";
	m_VirtKeys[37]	= 187;	m_Keys[37]	= "=";
	m_VirtKeys[38]	= 188;	m_Keys[38]	= ",";
	m_VirtKeys[39]	= 189;	m_Keys[39]	= "-";
	m_VirtKeys[40]	= 190;	m_Keys[40]  = ".";
	m_VirtKeys[41]	= 191;	m_Keys[41]	= "/";
	m_VirtKeys[42]	= 192;	m_Keys[42]  = "`";
	m_VirtKeys[43]	= 219;	m_Keys[43]	= "{";
	m_VirtKeys[44]	= 220;	m_Keys[44]	= "\\";
	m_VirtKeys[45]	= 221;	m_Keys[45]	= "}";
	m_VirtKeys[46]	= 222;	m_Keys[46]	= "\"";
	
	m_VirtKeys[47]	= 226;	m_Keys[47]	= "\\";
}
/*
	  else if (w>221)
			szTxt[0] = (char)w - 183;
		else if (w>218)
			szTxt[0] = (char)w - 128;
		else if (w == 192)
			szTxt[0] = (char)w - 96;
		else if (w>187)
			szTxt[0] = (char)w - 144;
		else if (w>186)
			szTxt[0] = (char)w - 126;
		else if (w>185)
			szTxt[0] = (char)w - 127;
		else if (w>184)
			szTxt[0] = (char)w - 126;
		else if (w>144)
			szTxt[0] = (char)w - 144;
		// convert to lowercase if the shiftbutton isn't
		// pressed and if w is a letter
		else if (w>64&&w<91)
			szTxt[0] = (char)w + 32;
		else
			szTxt[0] = (char)w;
	}
*/

/*	else if (GetKeyState(VK_SHIFT) & 0x8000)
	{
		switch (nVirtKey)
		{
			case 50 :	szTxt[0] = (char)nVirtKey + 14;
						break; // 2 -> @
			case 55 :	szTxt[0] = (char)nVirtKey - 17;
						break; // 8 -> *
			case 56	:	szTxt[0] = (char)nVirtKey - 14;
						break; // 8 -> *
			case 54 :	szTxt[0] = (char)nVirtKey + 40;
						break; // 6 -> ^
			case 186:	szTxt[0] = (char)nVirtKey - 128;
						break; // <
			case 187:	szTxt[0] = (char)nVirtKey - 144;
						break;
			case 188:	szTxt[0] = (char)nVirtKey - 128;
						break;
			case 189:	szTxt[0] = (char)nVirtKey - 94;
						break; // - -> _
			case 190 :  szTxt[0] = (char)nVirtKey - 128;
						break;
			case 191:	szTxt[0] = (char)nVirtKey - 128;
						break; // ?
			case 192 :  szTxt[0] = (char)nVirtKey - 66;
						break; // ?
			case 219:	szTxt[0] = (char)nVirtKey - 96;
						break; // {
			case 220:	szTxt[0] = (char)nVirtKey - 96;
						break;
			case 221:	szTxt[0] = (char)nVirtKey - 96;
						break; // }
			case 222 :	szTxt[0] = (char)nVirtKey - 188;
						break; // "
			default :	if (nVirtKey<65||nVirtKey>90)
							szTxt[0] = (char)nVirtKey - 16;
						else
							szTxt[0] = (char)nVirtKey;
		}
	else
	{
		switch (nVirtKey)
		{
			case 8	:	szTxt = "BACKSPACE";
						break;
			case 9	:	szTxt = "TAB";
						break;
			case 13	:	szTxt = "RETURN";
						break;
			case 16	:	szTxt = "SHIFT";
						return;
			case 17	:	szTxt = "CTRL";
						break;
			case 18	:	szTxt = "ALT";
						break;
			case 19	:	szTxt = "BREAK";
						break;
			case 20 :	szTxt = "CAPSLOCK";
						break;
			case 27	:	szTxt = "ESC";
						break;
			case 32	:	szTxt = "SPACE;
						break;						
			case 33 :	szTxt = "PAGEUP";
						break;
			case 34 :	szTxt = "PAGEDWN";
						break;			
			case 35 :	szTxt = "END";
						break;
			case 36 :	szTxt = "HOME";
						break;
			case 37 :	szTxt = "LEFT";
						break;
			case 38 :	szTxt = "UP";
						break;
			case 39 :	szTxt = "RIGHT";
						break;
			case 40 :	szTxt = "DOWN";
						break;
			case 44	:	szTxt = "PRINTSCREEN";
						break;
			case 45	:	szTxt = "INS";
						break;
			case 46	:	szTxt = "DEL";
						break;
			case 91	:	szTxt = "WIN-START";
						break;
			case 93	:	szTxt = "WIN-CONTEXT";
						break;
			default :	szTxt[0 ] = wVirtKey;
		}
	}	
*/