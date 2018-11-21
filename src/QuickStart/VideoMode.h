// VideoMode.h: interface for the CVideoMode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOMODE_H__C88037AD_5524_478E_8C17_86F43E3AAD28__INCLUDED_)
#define AFX_VIDEOMODE_H__C88037AD_5524_478E_8C17_86F43E3AAD28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVideoMode  
{
public:
	BOOL ChangeDisplayResolutionPermanently(LPDEVMODE pdm);
	BOOL GetCurrentVideoMode(DEVMODE* pdm);
	BOOL DecreaseDisplayResolutionPermanently();
	BOOL IncreaseDisplayResolutionPermanently();
	CVideoMode();
	virtual ~CVideoMode();

protected:
	BOOL IsSameExceptResolution(LPDEVMODE pdm1, LPDEVMODE pdm2);
};

#endif // !defined(AFX_VIDEOMODE_H__C88037AD_5524_478E_8C17_86F43E3AAD28__INCLUDED_)
