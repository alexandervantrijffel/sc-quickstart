// VideoMode.cpp: implementation of the CVideoMode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "VideoMode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoMode::CVideoMode()
{

}

CVideoMode::~CVideoMode()
{

}

BOOL CVideoMode::IncreaseDisplayResolutionPermanently()
{
	DEVMODE dmCur, dmPossible;
	dmCur.dmDriverExtra = dmPossible.dmDriverExtra = 0;
	dmCur.dmSize = dmPossible.dmSize = sizeof(DEVMODE);
	dmCur.dmFields = dmPossible.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY|DM_DISPLAYFLAGS;
		
	BOOL bRet=FALSE;
	int i=0;
	
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmCur))
	{
		while(EnumDisplaySettings( NULL, i++, &dmPossible))
		{
			if (IsSameExceptResolution(&dmCur, &dmPossible))
			{
				if (dmPossible.dmPelsWidth > dmCur.dmPelsWidth)	
					return ChangeDisplayResolutionPermanently(&dmPossible);
			}
		}

		// current display res is the highest -> set the lowest possible display res
		i=0;
		while(EnumDisplaySettings( NULL, i++, &dmPossible))
		{
			if (IsSameExceptResolution(&dmCur, &dmPossible))
				return ChangeDisplayResolutionPermanently(&dmPossible);
		}
	}

	return bRet;
}

BOOL CVideoMode::DecreaseDisplayResolutionPermanently()
{
	DEVMODE dmCur, dmPossible;
	dmCur.dmDriverExtra = dmPossible.dmDriverExtra = 0;
	dmCur.dmSize = dmPossible.dmSize = sizeof(DEVMODE);
	dmCur.dmFields = dmPossible.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY|DM_DISPLAYFLAGS;
		
	BOOL bRet=FALSE;
	int iIndexCur=0;
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmCur))
	{
		// search for the index of the current displaymode
		while(EnumDisplaySettings( NULL, iIndexCur, &dmPossible))
		{
			if (IsSameExceptResolution(&dmCur, &dmPossible))
			{
				if (dmPossible.dmPelsWidth == dmCur.dmPelsWidth)
				{
					bRet=TRUE;
					break;
				}
			}
			iIndexCur++;
		}
	}

	// get the resolution of the previous devmode
	if (bRet) // && iIndexCur if the current resolution is the lowest the highest resolution will be set
	{
		EnumDisplaySettings(NULL, iIndexCur-1, &dmPossible);
		return ChangeDisplayResolutionPermanently(&dmPossible);
	}

	return FALSE;
}

BOOL CVideoMode::GetCurrentVideoMode(DEVMODE *pdm)
{
  HDC hdc = ::GetDC(NULL);  // Screen DC used to get current display settings
  if (hdc == NULL)
    return FALSE;

  pdm->dmBitsPerPel = GetDeviceCaps(hdc, BITSPIXEL);
  pdm->dmPelsWidth	= GetDeviceCaps(hdc, HORZRES);
  pdm->dmPelsHeight	= GetDeviceCaps(hdc, VERTRES);
  pdm->dmDisplayFrequency = GetDeviceCaps(hdc, VREFRESH);
  
  ::ReleaseDC(NULL, hdc);

  return TRUE;
}

BOOL CVideoMode::ChangeDisplayResolutionPermanently(LPDEVMODE pdm)
{
	pdm->dmFields = DM_PELSWIDTH|DM_PELSHEIGHT;

	long lRet = ChangeDisplaySettings(pdm, CDS_UPDATEREGISTRY);
	
	CString szErr;
	switch (lRet)
	{
		//		DISP_CHANGE_SUCCESSFUL The settings change was successful. 
		case DISP_CHANGE_RESTART:
			szErr = _T("The computer must be restarted in order for the graphics mode to work.");
			break;
		case DISP_CHANGE_BADFLAGS:
			szErr = _T("An invalid set of flags was passed in.");
			break;
		case DISP_CHANGE_BADPARAM:
			szErr = _T("An invalid parameter was passed in");
			break;
		case DISP_CHANGE_FAILED:
			szErr = _T("The display driver failed the specified graphics mode.");
			break;
		case DISP_CHANGE_BADMODE:
			szErr = _T("The graphics mode is not supported.");
			break;
		case DISP_CHANGE_NOTUPDATED:
			szErr = _T("Unable to write settings to the registry.");
			break;
		default:
			return TRUE;
	}
	AfxMessageBox(szErr, MB_ICONEXCLAMATION);
	return FALSE;
}

BOOL CVideoMode::IsSameExceptResolution(LPDEVMODE pdm1, LPDEVMODE pdm2)
{
   return (    pdm1->dmBitsPerPel == pdm2->dmBitsPerPel 
			&& pdm1->dmDisplayFlags == pdm2->dmDisplayFlags
			&& pdm1->dmDisplayFrequency == pdm2->dmDisplayFrequency);
}
